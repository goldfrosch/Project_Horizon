#include "GA_LeapingCrush.h"

#include "AIController.h"
#include "PawnMotionWarpingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ProjectH/Characters/Boss/Kaurg/BossKaurg.h"
#include "ProjectH/GAS/_Common/Task/AT_PlayMontageWithEvent.h"
#include "ProjectH/Utils/MathUtil.h"

void UGA_LeapingCrush::ActivateAbility(const FGameplayAbilitySpecHandle Handle
										, const FGameplayAbilityActorInfo*
										ActorInfo
										, const FGameplayAbilityActivationInfo
										ActivationInfo
										, const FGameplayEventData*
										TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ABossKaurg* BossKaurg = Cast<ABossKaurg>(GetAvatarActorFromActorInfo());
	if (!BossKaurg->IsValidLowLevel())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	InitializeMotionWarpingPoint_Internal(BossKaurg);

	AT_LeapingMontageEvent = UAT_PlayMontageWithEvent::InitialEvent(
		this, NAME_None, LeapingAnimation, FGameplayTagContainer());

	AT_LeapingMontageEvent->OnCompleted.AddUniqueDynamic(
		this, &ThisClass::OnLeapingMontageEnd_Internal);

	AT_LeapingMontageEvent->ReadyForActivation();
}

void UGA_LeapingCrush::OnLeapingMontageEnd_Internal(FGameplayTag EventTag
													, FGameplayEventData
													EventData)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true
				, false);
}

void UGA_LeapingCrush::InitializeMotionWarpingPoint_Internal(
	ABossKaurg* BossKaurgPawn)
{
	const AAIController* BossKaurgPawnController = Cast<AAIController>(
		BossKaurgPawn->GetController());
	if (!BossKaurgPawnController->IsValidLowLevel())
	{
		return;
	}

	const FTransform StartTransform = GetAvatarActorFromActorInfo()->
		GetActorTransform();
	const FTransform TargetTransform = Cast<AActor>(
		BossKaurgPawnController->GetBlackboardComponent()->GetValueAsObject(
			"TargetActor"))->GetActorTransform();

	const FRotator TargetRotatorToView = {
		TargetTransform.GetRotation().Rotator().Pitch
		, FMath::UnwindDegrees(
			TargetTransform.GetRotation().Rotator().Yaw + 180.f)
		, TargetTransform.GetRotation().Rotator().Roll
	};

	FVector MiddlePoint = FMathUtil::GetMiddlePoint(
		StartTransform.GetLocation(), TargetTransform.GetLocation());

	// 보스룸의 천장이 없다는 가정하에 설정 (있어도 딱히 상관없다)
	// 있는 경우는 AbilityTask로 이후 설정 필요
	// TODO: 보스의 경우 점프력이라는 별도 스텟을 가지면 좋아보임
	MiddlePoint.Z += 1500;
	const FVector BezierPoint = FMathUtil::GetBezierPoint(
		StartTransform.GetLocation(), MiddlePoint, TargetTransform.GetLocation()
		, 0.5);

	BossKaurgPawn->GetPawnMotionWarpingComponent()->
					AddMotionWarpingLocationAndRotationData(
						TEXT("InAirLoc"), BezierPoint, TargetRotatorToView);

	BossKaurgPawn->GetPawnMotionWarpingComponent()->
					AddMotionWarpingLocationAndRotationData(
						TEXT("TargetLoc"), TargetTransform.GetLocation()
						, TargetRotatorToView);
}

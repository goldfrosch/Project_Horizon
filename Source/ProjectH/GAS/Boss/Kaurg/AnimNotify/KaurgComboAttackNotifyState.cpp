#include "KaurgComboAttackNotifyState.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ProjectH/Characters/Boss/Kaurg/BossKaurg.h"
#include "ProjectH/Characters/Boss/Kaurg/Components/BossKaurgCombatComponent.h"
#include "ProjectH/Utils/MathUtil.h"
#include "ProjectH/Utils/TraceUtil.h"

void UKaurgComboAttackNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp
												, UAnimSequenceBase* Animation
												, float TotalDuration
												, const
												FAnimNotifyEventReference&
												EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	const ABossKaurg* OwnerBoss = Cast<ABossKaurg>(MeshComp->GetOwner());

	if (!OwnerBoss)
	{
		return;
	}

	UBossKaurgCombatComponent* BossKaurgCombatComponent = OwnerBoss->
		GetBossKaurgCombatComponent();

	if (IsLeftEnabled)
	{
		BossKaurgCombatComponent->CaptureLeftHandPosition();
	}

	if (IsRightEnabled)
	{
		BossKaurgCombatComponent->CaptureRightHandPosition();
	}
}

void UKaurgComboAttackNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp
											, UAnimSequenceBase* Animation
											, float FrameDeltaTime
											, const FAnimNotifyEventReference&
											EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	const ABossKaurg* OwnerBoss = Cast<ABossKaurg>(MeshComp->GetOwner());

	if (!OwnerBoss)
	{
		return;
	}

	UBossKaurgCombatComponent* BossKaurgCombatComponent = OwnerBoss->
		GetBossKaurgCombatComponent();

	if (IsLeftEnabled)
	{
		const FVector PrevLeftLocation = BossKaurgCombatComponent->
			GetPrevLeftHandPosition();
		const FVector NextLeftLocation = BossKaurgCombatComponent->
										GetLeftHandAttackRegion()->
										GetComponentLocation();

		const FVector MidForceVector = (BossKaurgCombatComponent->
			GetPrevLeftHandForce() + BossKaurgCombatComponent->
									GetLeftHandAttackRegion()->
									GetForwardVector()) / 2;

		const FVector BezierMidPoint = FMathUtil::GetMiddlePoint(
			PrevLeftLocation
			, NextLeftLocation) + MidForceVector * FVector::Dist(
			PrevLeftLocation, NextLeftLocation) / LagDistance;

		DebugAttackPosition(MeshComp->GetOwner()->GetWorld(), PrevLeftLocation
							, BezierMidPoint, NextLeftLocation
							, BossKaurgCombatComponent->
							GetLeftHandAttackRegion());

		BossKaurgCombatComponent->CaptureLeftHandPosition();
	}

	if (IsRightEnabled)
	{
		const FVector NextRightLocation = BossKaurgCombatComponent->
										GetRightHandAttackRegion()->
										GetComponentLocation();

		BossKaurgCombatComponent->SetPrevLeftHandPosition(NextRightLocation);
	}
}

void UKaurgComboAttackNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp
											, UAnimSequenceBase* Animation
											, const FAnimNotifyEventReference&
											EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}

void UKaurgComboAttackNotifyState::DebugAttackPosition(
	const UWorld* World, const FVector& P0, const FVector& P1, const FVector& P2
	, const UBoxComponent* AttackBox)
{
	const float Distance = FVector::Dist(P0, P2);
	// 보간 갯수
	const uint16 InterpCount = FMath::CeilToInt(
		FMath::Abs(Distance) / LagDistance);

	UKismetSystemLibrary::DrawDebugLine(World, P0, P2, FLinearColor::Red, 1, 1);

	TArray<AActor*> IgnoreActors;
	TArray<FHitResult> HitResults;

	FSquareTraceParams TraceParams;
	TraceParams.World = World;
	TraceParams.IgnoreActors = IgnoreActors;
	TraceParams.HitResults = HitResults;

	TraceParams.IsShowDebugTrace = true;
	TraceParams.SquareExtents = AttackBox->GetScaledBoxExtent();

	for (int i = 0; i <= InterpCount; i++)
	{
		const float Percent = InterpCount == 0
								? 1
								: i / static_cast<float>(InterpCount);

		const FVector BezierPoint = FMathUtil::GetBezierPoint(
			P0, P1, P2, Percent);

		TraceParams.SquareInfo.Position = BezierPoint;
		TraceParams.SquareInfo.ForwardVector = AttackBox->GetForwardVector();
		TraceParams.SquareInfo.UpVector = AttackBox->GetUpVector();

		FTraceUtil::SquareTraceMulti(TraceParams);
	}
}

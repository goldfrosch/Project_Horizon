#include "GA_LeapingCrush_Quake.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ProjectH/Characters/Boss/Kaurg/BossKaurg.h"

void UGA_LeapingCrush_Quake::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle
	, const FGameplayAbilityActorInfo* ActorInfo
	, const FGameplayAbilityActivationInfo ActivationInfo
	, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	Index = 0;
	CurrentRange = 0.f;

	if (QuakeParams.Num() == 0)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	QuakeAttack_Internal();
}

void UGA_LeapingCrush_Quake::EndAbility(const FGameplayAbilitySpecHandle Handle
										, const FGameplayAbilityActorInfo*
										ActorInfo
										, const FGameplayAbilityActivationInfo
										ActivationInfo
										, bool bReplicateEndAbility
										, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility
					, bWasCancelled);

	GetWorld()->GetTimerManager().ClearTimer(QuakeTimerHandle);
}

void UGA_LeapingCrush_Quake::QuakeAttack_Internal()
{
	ABossKaurg* BossKaurg = Cast<ABossKaurg>(GetAvatarActorFromActorInfo());
	if (!BossKaurg->IsValidLowLevel())
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo
					, true, true);
		return;
	}

	const FLeapingCrushQuakeParam& QuakeParam = QuakeParams[Index];

	const float StartRange = CurrentRange;
	const float EndRange = CurrentRange + QuakeParam.GetRange();

	CurrentRange = EndRange;

	const FVector SelfLocation = BossKaurg->GetFootPos()->GetComponentLocation()
		+ BossKaurg->GetActorLocation();

	TArray<AActor*> IgnoreList;
	IgnoreList.Add(BossKaurg);

	TArray<FHitResult> HitResults;
	UKismetSystemLibrary::SphereTraceMulti(GetWorld(), SelfLocation
											, SelfLocation, EndRange
											, TraceTypeQuery1, true, IgnoreList
											, EDrawDebugTrace::ForDuration
											, HitResults, true);

	for (const FHitResult& HitResult : HitResults)
	{
		const float ZValue = FMath::Abs(
			HitResult.GetActor()->GetActorLocation().Z - BossKaurg->
			GetActorLocation().Z);

		const float Distance = FVector::Dist(
			HitResult.GetActor()->GetActorLocation()
			, BossKaurg->GetActorLocation());

		if (ZValue > ZLerpValue && Distance < StartRange)
		{
			continue;
		}

		// TODO: 데미지 입력 로직
		if (UAbilitySystemComponent* ASC =
			UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(
				HitResult.GetActor()))
		{
			UE_LOG(LogTemp, Display, TEXT("데미지 입력 로직 : %s")
					, *HitResult.GetActor()->GetName());
		}
	}

	Index += 1;

	if (Index == QuakeParams.Num())
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo
					, true, false);
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(QuakeTimerHandle, this
											, &ThisClass::QuakeAttack_Internal
											, QuakeParam.GetDelayTime(), false);
}

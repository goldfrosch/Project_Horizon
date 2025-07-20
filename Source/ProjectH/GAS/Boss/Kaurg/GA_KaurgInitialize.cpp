#include "GA_KaurgInitialize.h"

#include "ProjectH/GAS/_Common/Task/AT_PlayMontageWithEvent.h"

void UGA_KaurgInitialize::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle
	, const FGameplayAbilityActorInfo* ActorInfo
	, const FGameplayAbilityActivationInfo ActivationInfo
	, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AT_RoarMontageEvent = UAT_PlayMontageWithEvent::InitialEvent(
		this, NAME_None, RoarMontage, FGameplayTagContainer());
	AT_RoarMontageEvent->OnCompleted.AddUniqueDynamic(
		this, &ThisClass::OnRoarMontageEnd_Internal);

	AT_RoarMontageEvent->ReadyForActivation();
}

void UGA_KaurgInitialize::OnRoarMontageEnd_Internal(FGameplayTag EventTag
													, FGameplayEventData
													EventData)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true
				, false);
}

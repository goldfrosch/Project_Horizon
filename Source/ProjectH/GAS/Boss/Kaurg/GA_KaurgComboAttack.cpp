#include "GA_KaurgComboAttack.h"

#include "ProjectH/GAS/_Common/Task/AT_PlayMontageWithEvent.h"

void UGA_KaurgComboAttack::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle
	, const FGameplayAbilityActorInfo* ActorInfo
	, const FGameplayAbilityActivationInfo ActivationInfo
	, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AT_ComboAttackMontageEvent = UAT_PlayMontageWithEvent::InitialEvent(
		this, NAME_None, ComboAttackMontages[ComboIndex]
		, FGameplayTagContainer());

	AT_ComboAttackMontageEvent->OnCompleted.AddUniqueDynamic(
		this, &ThisClass::OnAttackEnd);
	AT_ComboAttackMontageEvent->ReadyForActivation();
}

void UGA_KaurgComboAttack::EndAbility(const FGameplayAbilitySpecHandle Handle
									, const FGameplayAbilityActorInfo* ActorInfo
									, const FGameplayAbilityActivationInfo
									ActivationInfo, bool bReplicateEndAbility
									, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility
					, bWasCancelled);

	if (ComboIndex >= ComboAttackMontages.Num())
	{
		ComboIndex = 0;
	}
}

void UGA_KaurgComboAttack::OnAttackEnd(FGameplayTag EventTag
										, FGameplayEventData EventData)
{
	ComboIndex += 1;
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo()
				, GetCurrentActivationInfo(), true, false);
}

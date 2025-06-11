#include "GA_PlayerSprint.h"

#include "ProjectH/GAS/_Common/Attribute/ATR_BaseAttribute.h"

void UGA_PlayerSprint::ActivateAbility(const FGameplayAbilitySpecHandle Handle
										, const FGameplayAbilityActorInfo*
										ActorInfo
										, const FGameplayAbilityActivationInfo
										ActivationInfo
										, const FGameplayEventData*
										TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const FGameplayEffectContextHandle EffectContext =
		GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	const FGameplayEffectSpecHandle EffectSpec =
		GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
			SprintEffect, 1.0f, EffectContext);

	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToSelf(
		*EffectSpec.Data.Get());
}

void UGA_PlayerSprint::EndAbility(const FGameplayAbilitySpecHandle Handle
								, const FGameplayAbilityActorInfo* ActorInfo
								, const FGameplayAbilityActivationInfo
								ActivationInfo, bool bReplicateEndAbility
								, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility
					, bWasCancelled);
	GetAbilitySystemComponentFromActorInfo()->
		RemoveActiveGameplayEffectBySourceEffect(
			SprintEffect, GetAbilitySystemComponentFromActorInfo());
}

void UGA_PlayerSprint::InputReleased(const FGameplayAbilitySpecHandle Handle
									, const FGameplayAbilityActorInfo* ActorInfo
									, const FGameplayAbilityActivationInfo
									ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

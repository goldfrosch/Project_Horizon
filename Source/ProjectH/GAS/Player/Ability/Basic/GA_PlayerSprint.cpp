#include "GA_PlayerSprint.h"

#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "ProjectH/Characters/Player/PlayerCharacter.h"
#include "ProjectH/GAS/_Common/Attribute/ATR_BaseAttribute.h"
#include "ProjectH/GAS/_Common/Task/AT_PlayMontageWithEvent.h"
#include "ProjectH/Utils/LocateUtil.h"

void UGA_PlayerSprint::ActivateAbility(const FGameplayAbilitySpecHandle Handle
										, const FGameplayAbilityActorInfo*
										ActorInfo
										, const FGameplayAbilityActivationInfo
										ActivationInfo
										, const FGameplayEventData*
										TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AT_SprintDelay = UAbilityTask_WaitDelay::WaitDelay(this, HoldExistTime);
	AT_SprintDelay->OnFinish.AddUniqueDynamic(this, &ThisClass::OnSprintReady);
	AT_SprintDelay->ReadyForActivation();

	ExistTime = FDateTime::Now();
}

void UGA_PlayerSprint::InputReleased(const FGameplayAbilitySpecHandle Handle
									, const FGameplayAbilityActorInfo* ActorInfo
									, const FGameplayAbilityActivationInfo
									ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);

	const float HoldTime = (FDateTime::Now() - ExistTime).GetTotalSeconds();
	if (HoldTime > HoldExistTime)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	const APlayerCharacter* Player = Cast<APlayerCharacter>(
		GetAvatarActorFromActorInfo());
	if (!Player)
	{
		return;
	}

	const float Angle = FLocateUtil::GetDeltaAngle(
		Player->GetVelocity(), Player->GetActorForwardVector());

	// 구르기 실행
	AT_RollActionMontage = UAT_PlayMontageWithEvent::InitialEvent(
		this, NAME_None, RollAnims[FLocateUtil::GetDirectionByAngle(Angle)]
		, FGameplayTagContainer());

	AT_RollActionMontage->OnCompleted.AddUniqueDynamic(
		this, &ThisClass::OnRollActionEnd);
	AT_RollActionMontage->ReadyForActivation();
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

void UGA_PlayerSprint::OnSprintReady()
{
	const FGameplayEffectContextHandle EffectContext =
		GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	const FGameplayEffectSpecHandle EffectSpec =
		GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
			SprintEffect, 1.0f, EffectContext);

	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToSelf(
		*EffectSpec.Data.Get());
}

void UGA_PlayerSprint::OnRollActionEnd(FGameplayTag EventTag
										, FGameplayEventData EventData)
{
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo()
				, GetCurrentActivationInfo(), true, false);
}

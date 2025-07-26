#pragma once

#include "CoreMinimal.h"
#include "ProjectH/GAS/_Common/Ability/GA_BaseAbility.h"
#include "GA_KaurgComboAttack.generated.h"

class UAT_PlayMontageWithEvent;

UCLASS()
class PROJECTH_API UGA_KaurgComboAttack : public UGA_BaseAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle
								, const FGameplayAbilityActorInfo* ActorInfo
								, const FGameplayAbilityActivationInfo
								ActivationInfo
								, const FGameplayEventData*
								TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle
							, const FGameplayAbilityActorInfo* ActorInfo
							, const FGameplayAbilityActivationInfo
							ActivationInfo, bool bReplicateEndAbility
							, bool bWasCancelled) override;

private:
	UPROPERTY()
	TObjectPtr<UAT_PlayMontageWithEvent> AT_ComboAttackMontageEvent;

	UPROPERTY(EditDefaultsOnly, Category = "Options|Anim"
		, meta = (AllowPrivateAccess = true))
	TArray<TObjectPtr<UAnimMontage>> ComboAttackMontages;

	uint8 ComboIndex = 0;

	UFUNCTION()
	void OnAttackEnd(FGameplayTag EventTag, FGameplayEventData EventData);
};

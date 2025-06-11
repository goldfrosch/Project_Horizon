#pragma once

#include "CoreMinimal.h"
#include "ProjectH/GAS/_Common/Ability/GA_BaseInputAbility.h"
#include "GA_PlayerSprint.generated.h"

UCLASS()
class PROJECTH_API UGA_PlayerSprint : public UGA_BaseInputAbility
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

	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle
								, const FGameplayAbilityActorInfo* ActorInfo
								, const FGameplayAbilityActivationInfo
								ActivationInfo) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Options"
		, meta = (AllowPrivateAccess = true))
	TSubclassOf<UGameplayEffect> SprintEffect;
};

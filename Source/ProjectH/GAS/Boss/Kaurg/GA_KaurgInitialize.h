#pragma once

#include "CoreMinimal.h"
#include "ProjectH/GAS/_Common/Ability/GA_BaseAbility.h"
#include "GA_KaurgInitialize.generated.h"

class UAT_PlayMontageWithEvent;

UCLASS()
class PROJECTH_API UGA_KaurgInitialize : public UGA_BaseAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle
								, const FGameplayAbilityActorInfo* ActorInfo
								, const FGameplayAbilityActivationInfo
								ActivationInfo
								, const FGameplayEventData*
								TriggerEventData) override;

private:
	UPROPERTY()
	TObjectPtr<UAT_PlayMontageWithEvent> AT_RoarMontageEvent;

	UPROPERTY(EditDefaultsOnly, Category = "Options"
		, meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> RoarMontage;

	UFUNCTION()
	void OnRoarMontageEnd_Internal(FGameplayTag EventTag
									, FGameplayEventData EventData);
};

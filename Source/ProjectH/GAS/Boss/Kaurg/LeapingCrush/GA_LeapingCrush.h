#pragma once

#include "CoreMinimal.h"
#include "ProjectH/GAS/_Common/Ability/GA_BaseAbility.h"
#include "GA_LeapingCrush.generated.h"

class ABossKaurg;
class UAT_PlayMontageWithEvent;

UCLASS()
class PROJECTH_API UGA_LeapingCrush : public UGA_BaseAbility
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
	TObjectPtr<UAT_PlayMontageWithEvent> AT_LeapingMontageEvent;

	UPROPERTY(EditDefaultsOnly, Category = "Options"
		, meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> LeapingAnimation;

	UFUNCTION()
	void OnLeapingMontageEnd_Internal(FGameplayTag EventTag
									, FGameplayEventData EventData);

	void InitializeMotionWarpingPoint_Internal(ABossKaurg* BossKaurgPawn);
};

#pragma once

#include "CoreMinimal.h"
#include "ProjectH/GAS/_Common/Ability/GA_BaseAbility.h"
#include "GA_LeapingCrush_Quake.generated.h"

USTRUCT()
struct PROJECTH_API FLeapingCrushQuakeParam
{
	GENERATED_USTRUCT_BODY()

	GETTER(float, DelayTime)
	GETTER(float, Range)

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	float DelayTime = 0.f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	float Range = 0.f;
};

UCLASS()
class PROJECTH_API UGA_LeapingCrush_Quake : public UGA_BaseAbility
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
	UPROPERTY(EditDefaultsOnly, Category = "Options"
		, meta = (AllowPrivateAccess = true))
	TArray<FLeapingCrushQuakeParam> QuakeParams;

	UPROPERTY(EditDefaultsOnly, Category = "Options"
		, meta = (AllowPrivateAccess = true))
	float ZLerpValue = 10.f;

	FTimerHandle QuakeTimerHandle;

	UFUNCTION()
	void QuakeAttack_Internal();

	uint8 Index = 0;
	float CurrentRange = 0.f;
};

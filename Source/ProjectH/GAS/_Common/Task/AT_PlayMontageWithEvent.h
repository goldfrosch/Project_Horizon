#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AT_PlayMontageWithEvent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayMontageWithEventNotified
											, FGameplayTag, EventTag
											, FGameplayEventData, EventData);

UCLASS()
class PROJECTH_API UAT_PlayMontageWithEvent : public UAbilityTask
{
	GENERATED_BODY()

public:
	UAT_PlayMontageWithEvent();

	virtual void Activate() override;
	virtual void ExternalCancel() override;
	virtual FString GetDebugString() const override;
	virtual void OnDestroy(bool AbilityEnded) override;

	UPROPERTY()
	UAnimMontage* PlayAnimMontage;

	UPROPERTY(BlueprintAssignable)
	FOnPlayMontageWithEventNotified OnCompleted;

	UPROPERTY(BlueprintAssignable)
	FOnPlayMontageWithEventNotified OnBlendOut;

	UPROPERTY(BlueprintAssignable)
	FOnPlayMontageWithEventNotified OnInterrupted;

	UPROPERTY(BlueprintAssignable)
	FOnPlayMontageWithEventNotified OnCancelled;

	UPROPERTY(BlueprintAssignable)
	FOnPlayMontageWithEventNotified EventReceived;

	static UAT_PlayMontageWithEvent* InitialEvent(
		UGameplayAbility* OwningAbility, FName TaskInstanceName
		, UAnimMontage* MontageToPlay, FGameplayTagContainer EventTags
		, FGameplayEventData EventData = FGameplayEventData(), float Rate = 1.f
		, FName StartSection = NAME_None, bool bStopWhenAbilityEnds = false
		, float AnimRootMotionTranslationScale = 1.f);

private:
	UPROPERTY()
	FName StartSection;

	UPROPERTY()
	FGameplayTagContainer EventTags;

	UPROPERTY()
	FGameplayEventData EventData = FGameplayEventData();

	UPROPERTY()
	float Rate;

	UPROPERTY()
	bool bStopWhenAbilityEnds;

	UPROPERTY()
	float AnimRootMotionTranslationScale = 1.f;

	void OnGameplayEvent(FGameplayTag EventTag
						, const FGameplayEventData* Payload);
	void OnAbilityCancelled();

	void OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted);
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	bool StopPlayingMontage();

	FDelegateHandle EventHandle;
	FDelegateHandle CancelledHandle;
	FOnMontageEnded MontageEndedDelegate;
	FOnMontageBlendingOutStarted BlendingOutDelegate;
};

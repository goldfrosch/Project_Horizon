#pragma once

#include "CoreMinimal.h"
#include "GA_BaseAbility.h"
#include "GA_BaseInputAbility.generated.h"

enum class EAbilityInputId : uint8;
class UInputAction;
class UHorizonAbilitySystemComponent;

UCLASS()
class PROJECTH_API UGA_BaseInputAbility : public UGA_BaseAbility
{
	GENERATED_BODY()

public:
	UGA_BaseInputAbility(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadWrite, EditAnywhere
		, Category = "Custom Gameplay Ability")
	bool ActivateAbilityOnGranted = false;
	
	virtual bool InitializeAbility(UHorizonAbilitySystemComponent* ASC) override;

	GETTER(EAbilityInputId, InputId)

protected:
	uint32 TriggeredEventHandle = -1;

	void SetupEnhancedInputBindings(const FGameplayAbilityActorInfo* ActorInfo
									, const FGameplayAbilitySpec& Spec);

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo
							, const FGameplayAbilitySpec& Spec) override;

	virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo
								, const FGameplayAbilitySpec& Spec) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle
							, const FGameplayAbilityActorInfo* ActorInfo
							, const FGameplayAbilityActivationInfo
							ActivationInfo, bool bReplicateEndAbility
							, bool bWasCancelled) override;

	UPROPERTY(EditDefaultsOnly, Category = "Options"
		, meta = (AllowPrivateAccess = true))
	bool IsPassive;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Options|Input"
		, meta = (AllowPrivateAccess = true, EditCondition = "!IsPassive"))
	TObjectPtr<UInputAction> ActivationInputAction;

	void OnAbilityInputPressed(const FGameplayAbilityActorInfo* ActorInfo);

	void OnAbilityInputReleased(const FGameplayAbilityActorInfo* ActorInfo);
	
	UPROPERTY(EditDefaultsOnly, Category = "Options|Input"
		, meta = (AllowPrivateAccess = true, EditCondition = "!IsPassive"))
	EAbilityInputId InputId;
};

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "ProjectH/GAS/_Common/Attribute/ATR_BaseAttribute.h"
#include "BaseCharacter.generated.h"

class UATR_BaseAttribute;
struct FOnAttributeChangeData;
class UHorizonAbilitySystemInitializeData;
class UHorizonAbilitySystemComponent;
class UInputComponent;

UCLASS()
class PROJECTH_API ABaseCharacter
	: public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Options|GAS")
	TObjectPtr<UHorizonAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UATR_BaseAttribute> Attribute;

	virtual void BeginPlay() override;

	virtual void InitializeAbilitySystem();

	void OnHealthChanged(const FOnAttributeChangeData& Data);

	void OnMovementSpeedChanged(const FOnAttributeChangeData& Data);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Options|GAS"
		, meta = (AllowPrivateAccess = true))
	TObjectPtr<UHorizonAbilitySystemInitializeData> AbilitySystemInitializeData;
};

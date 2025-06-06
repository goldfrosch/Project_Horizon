#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UHorizonAbilitySystemInitializeData;
class UHorizonAbilitySystemComponent;
class UInputComponent;

UCLASS()
class PROJECTH_API ABaseCharacter : public ACharacter,
									public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Options|GAS")
	TObjectPtr<UHorizonAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Options|GAS")
	TObjectPtr<UHorizonAbilitySystemInitializeData> InitializeData;
	
	virtual void BeginPlay() override;
	
	virtual void InitializeAbilitySystem() {}
};

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class UHorizonAbilitySystemInitializeData;
class UHorizonAbilitySystemComponent;

UCLASS()
class PROJECTH_API ABaseWeapon : public AActor,
								 public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseWeapon();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void EquipWeapon(AActor* NewOwner);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Options|GAS")
	TObjectPtr<UHorizonAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Options|GAS")
	TObjectPtr<UHorizonAbilitySystemInitializeData> InitializeData;
	
	virtual void BeginPlay() override;
	
	virtual void InitializeAbilitySystem() {}
};

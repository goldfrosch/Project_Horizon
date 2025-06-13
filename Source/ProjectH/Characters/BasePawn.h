#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "ProjectH/Utils/MacroUtil.h"

#include "BasePawn.generated.h"

class UHorizonAbilitySystemInitializeData;
class UHorizonAbilitySystemComponent;
class UATR_BaseAttribute;
struct FOnAttributeChangeData;

UCLASS()
class PROJECTH_API ABasePawn : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABasePawn();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	GETTER_EDITABLE(TObjectPtr<USkeletalMeshComponent>, Mesh)

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Options|GAS")
	TObjectPtr<UHorizonAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UATR_BaseAttribute> Attribute;

	virtual void InitializeAbilitySystem();

	void OnHealthChanged(const FOnAttributeChangeData& Data);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Options|GAS"
		, meta = (AllowPrivateAccess = true))
	TObjectPtr<UHorizonAbilitySystemInitializeData> AbilitySystemInitializeData;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> Mesh;
};

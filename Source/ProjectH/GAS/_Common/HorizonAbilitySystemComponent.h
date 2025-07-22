#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ProjectH/Utils/MacroUtil.h"
#include "HorizonAbilitySystemComponent.generated.h"

class UHorizonAbilitySystemInitializeData;

UCLASS()
class PROJECTH_API UHorizonAbilitySystemComponent
	: public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UHorizonAbilitySystemComponent();

	void Initialize();

	GETTER_SETTER(bool, IsInitialize)
	GETTER(uint16, Level)

private:
	UPROPERTY(EditDefaultsOnly, Category = "Options"
		, meta = (AllowPrivateAccess = true))
	uint16 Level = 1;

	bool IsInitialize = false;

	UPROPERTY(EditDefaultsOnly, Category = "Options"
		, meta = (AllowPrivateAccess = true))
	TObjectPtr<UHorizonAbilitySystemInitializeData> AbilitySystemInitializeData;
};

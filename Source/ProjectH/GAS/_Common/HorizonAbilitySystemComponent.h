#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ProjectH/Utils/MacroUtil.h"
#include "HorizonAbilitySystemComponent.generated.h"

UCLASS()
class PROJECTH_API UHorizonAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	UHorizonAbilitySystemComponent();

	void Initialize(class UHorizonAbilitySystemInitializeData* InitialData);

	GETTER_SETTER(bool, IsInitialize)

private:
	bool IsInitialize = false;
};

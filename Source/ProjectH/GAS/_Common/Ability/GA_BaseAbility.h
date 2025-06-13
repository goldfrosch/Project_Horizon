#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ProjectH/Utils/MacroUtil.h"
#include "GA_BaseAbility.generated.h"

class UHorizonAbilitySystemComponent;

UCLASS()
class PROJECTH_API UGA_BaseAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	GETTER(bool, IsInitialized)

	virtual bool InitializeAbility(UHorizonAbilitySystemComponent* ASC);

protected:
	bool IsInitialized = false;
};

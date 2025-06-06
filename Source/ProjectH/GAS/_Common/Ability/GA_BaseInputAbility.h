#pragma once

#include "CoreMinimal.h"
#include "GA_BaseAbility.h"
#include "GA_BaseInputAbility.generated.h"

enum class EAbilityInputId : uint8;
class UHorizonAbilitySystemComponent;

UCLASS()
class PROJECTH_API UGA_BaseInputAbility : public UGA_BaseAbility
{
	GENERATED_BODY()

public:
	virtual bool InitializeAbility(UHorizonAbilitySystemComponent* ASC) override;

	GETTER(EAbilityInputId, InputId)
	
private:
	EAbilityInputId InputId;
};

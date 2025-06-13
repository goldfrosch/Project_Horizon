#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "ProjectH/Utils/MacroUtil.h"
#include "BasePlayerState.generated.h"

class UATR_PlayerAttribute;
class UHorizonAbilitySystemComponent;

UCLASS()
class PROJECTH_API ABasePlayerState
	: public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABasePlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	GETTER_EDITABLE(TObjectPtr<UATR_PlayerAttribute>, AttributeSet)

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UHorizonAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UATR_PlayerAttribute> AttributeSet;
};

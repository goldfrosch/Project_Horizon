#include "BasePlayerState.h"

#include "ProjectH/GAS/Player/Attribute/ATR_PlayerAttribute.h"
#include "ProjectH/GAS/_Common/HorizonAbilitySystemComponent.h"

ABasePlayerState::ABasePlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<
		UHorizonAbilitySystemComponent>("Ability System Component");

	AttributeSet = CreateDefaultSubobject<UATR_PlayerAttribute>(
		TEXT("Attribute Set"));
}

void ABasePlayerState::BeginPlay()
{
	Super::BeginPlay();
}

UAbilitySystemComponent* ABasePlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

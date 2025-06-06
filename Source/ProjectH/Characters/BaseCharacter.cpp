#include "BaseCharacter.h"
#include "ProjectH/GAS/_Common/HorizonAbilitySystemComponent.h"


ABaseCharacter::ABaseCharacter()
{
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


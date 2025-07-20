#include "BaseCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "ProjectH/GAS/_Common/HorizonAbilitySystemComponent.h"
#include "ProjectH/GAS/_Common/Attribute/ATR_BaseAttribute.h"
#include "ProjectH/GAS/_Common/Tag/HorizonGameplayTag.h"


ABaseCharacter::ABaseCharacter()
{
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABaseCharacter::InitializeAbilitySystem()
{
	AbilitySystemComponent->Initialize();
	AbilitySystemComponent->
		GetGameplayAttributeValueChangeDelegate(
			Attribute->GetMoveSpeedAttribute()).AddUObject(
			this, &ThisClass::OnMovementSpeedChanged);
	AbilitySystemComponent->
		GetGameplayAttributeValueChangeDelegate(Attribute->GetHealthAttribute())
		.AddUObject(this, &ThisClass::OnHealthChanged);
}

void ABaseCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	const float NewHealth = Data.NewValue;

	Attribute->SetHealth(NewHealth > 0 ? NewHealth : 0);

	if (Attribute->GetHealth() == 0)
	{
		FGameplayTagContainer TagContainer;
		TagContainer.AddTag(HorizonGameplayTags::Default_Passive_Died);

		AbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);
	}
}

void ABaseCharacter::OnMovementSpeedChanged(const FOnAttributeChangeData& Data)
{
	const float NewMovementSpeed = Data.NewValue;

	GetCharacterMovement()->MaxWalkSpeed = NewMovementSpeed;
}

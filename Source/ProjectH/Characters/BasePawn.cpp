#include "BasePawn.h"
#include "ProjectH/GAS/_Common/HorizonAbilitySystemComponent.h"
#include "ProjectH/GAS/_Common/Attribute/ATR_BaseAttribute.h"
#include "ProjectH/GAS/_Common/Tag/HorizonGameplayTag.h"


ABasePawn::ABasePawn()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
}

UAbilitySystemComponent* ABasePawn::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABasePawn::InitializeAbilitySystem()
{
	AbilitySystemComponent->Initialize(AbilitySystemInitializeData);
	AbilitySystemComponent->
		GetGameplayAttributeValueChangeDelegate(Attribute->GetHealthAttribute())
		.AddUObject(this, &ThisClass::OnHealthChanged);
}

void ABasePawn::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	const float NewHealth = Data.NewValue;

	Attribute->SetHealth(NewHealth > 0 ? NewHealth : 0);

	if (Attribute->GetHealth() == 0)
	{
		FGameplayTagContainer TagContainer;
		TagContainer.AddTag(HorizonGameplayTags::Passive_Died);

		AbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);
	}
}

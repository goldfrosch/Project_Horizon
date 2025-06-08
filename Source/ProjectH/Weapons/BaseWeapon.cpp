#include "BaseWeapon.h"
#include "ProjectH/GAS/_Common/HorizonAbilitySystemComponent.h"

ABaseWeapon::ABaseWeapon()
{
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

UAbilitySystemComponent* ABaseWeapon::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABaseWeapon::EquipWeapon(AActor* NewOwner)
{
	SetOwner(NewOwner);
}

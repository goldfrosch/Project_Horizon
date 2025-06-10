#include "ATR_BaseAttribute.h"
#include "Net/UnrealNetwork.h"

void UATR_BaseAttribute::GetLifetimeReplicatedProps(
	TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	
	DOREPLIFETIME_CONDITION_NOTIFY(UATR_BaseAttribute, Health, COND_None
																, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UATR_BaseAttribute, MaxHealth, COND_None
																, REPNOTIFY_Always);
}


void UATR_BaseAttribute::PreAttributeChange(const FGameplayAttribute& Attribute
	, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UATR_BaseAttribute::OnRepHealth(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UATR_BaseAttribute, Health, OldHealth);
}

void UATR_BaseAttribute::OnRepMaxHealth(
	const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UATR_BaseAttribute, MaxHealth, OldMaxHealth);
}

void UATR_BaseAttribute::OnRepMovementSpeed(
	const FGameplayAttributeData& OldMovementSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UATR_BaseAttribute, MovementSpeed, OldMovementSpeed);
}

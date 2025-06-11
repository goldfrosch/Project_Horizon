#include "ATR_PlayerAttribute.h"
#include "Net/UnrealNetwork.h"

void UATR_PlayerAttribute::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UATR_PlayerAttribute, Mana, COND_None
																, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UATR_PlayerAttribute, MaxMana, COND_None
																, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UATR_PlayerAttribute, Stamina, COND_None
																, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UATR_PlayerAttribute, MaxStamina, COND_None
																, REPNOTIFY_Always);
}


void UATR_PlayerAttribute::PreAttributeChange(
	const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UATR_PlayerAttribute::OnRepMana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UATR_PlayerAttribute, Mana, OldMana);
}

void UATR_PlayerAttribute::OnRepMaxMana(
	const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UATR_PlayerAttribute, MaxMana, OldMaxMana);
}

void UATR_PlayerAttribute::OnRepStamina(
	const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UATR_PlayerAttribute, Stamina, OldStamina);
}

void UATR_PlayerAttribute::OnRepMaxStamina(
	const FGameplayAttributeData& OldMaxStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UATR_PlayerAttribute, MaxStamina, OldMaxStamina);
}

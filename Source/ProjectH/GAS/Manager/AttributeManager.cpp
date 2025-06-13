#include "AttributeManager.h"

#include "ProjectH/GAS/AbilitySystemStruct.h"
#include "ProjectH/GAS/Player/Attribute/ATR_PlayerAttribute.h"

TUniquePtr<FAttributeManager> FAttributeManager::AttributeManager = nullptr;

FAttributeManager* FAttributeManager::GetAttributeManager()
{
	if (!AttributeManager.IsValid())
	{
		AttributeManager = MakeUnique<FAttributeManager>();
	}

	return AttributeManager.Get();
}

void FAttributeManager::InitializeAttributeData()
{
	InitializePlayerAttributeData_Internal();
}

void FAttributeManager::InitPlayerAttribute(const FString& Key
											, UATR_PlayerAttribute*
											PlayerAttribute)
{
	const FATR_PlayerAttributeTable& Data = PlayerAttributeInfo[Key];

	PlayerAttribute->InitHealth(Data.GetBaseHealth());
	PlayerAttribute->InitMaxHealth(Data.GetBaseHealth());

	PlayerAttribute->InitMana(Data.GetBaseMana());
	PlayerAttribute->InitMaxMana(Data.GetBaseMana());

	PlayerAttribute->InitStamina(Data.GetBaseStamina());
	PlayerAttribute->InitMaxStamina(Data.GetBaseStamina());

	PlayerAttribute->InitMoveSpeed(Data.GetBaseMoveSpeed());
}

void FAttributeManager::InitializePlayerAttributeData_Internal()
{
	const static ConstructorHelpers::FObjectFinder<UDataTable>
		TempPlayerAttributeDataTable(TEXT(
			"/Game/Characters/Datas/DT_PlayerAttribute.DT_PlayerAttribute"));

	if (!TempPlayerAttributeDataTable.Succeeded())
	{
		return;
	}

	for (const auto& PlayerAttribute : TempPlayerAttributeDataTable.Object->
		GetRowMap())
	{
		const FATR_PlayerAttributeTable* PlayerAttributeValue = reinterpret_cast
			<FATR_PlayerAttributeTable*>(PlayerAttribute.Value);
		PlayerAttributeInfo.Add(PlayerAttribute.Key.ToString()
								, *PlayerAttributeValue);
	}
}

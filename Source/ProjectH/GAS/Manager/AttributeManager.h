#pragma once

#include "ProjectH/GAS/AbilitySystemStruct.h"

class UATR_PlayerAttribute;

class FAttributeManager
{
public:
	static FAttributeManager* GetAttributeManager();

	void InitializeAttributeData();
	void InitPlayerAttribute(const FString& Key
							, UATR_PlayerAttribute* PlayerAttribute);

private:
	static TUniquePtr<FAttributeManager> AttributeManager;

	void InitializePlayerAttributeData_Internal();

	TMap<FString, FATR_PlayerAttributeTable> PlayerAttributeInfo;
};

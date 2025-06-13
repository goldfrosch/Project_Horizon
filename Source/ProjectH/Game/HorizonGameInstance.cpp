#include "HorizonGameInstance.h"

#include "ProjectH/GAS/Manager/AttributeManager.h"

UHorizonGameInstance::UHorizonGameInstance()
{
	FAttributeManager::GetAttributeManager()->InitializeAttributeData();
}

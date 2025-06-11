#pragma once

#include "ProjectH/Utils/MacroUtil.h"
#include "AbilitySystemStruct.generated.h"

USTRUCT(BlueprintType)
struct PROJECTH_API FATR_PlayerAttributeTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	GETTER(uint16, BaseHealth)
	GETTER(uint16, BaseMana)
	GETTER(uint16, BaseStamina)
	GETTER(uint16, BaseMoveSpeed)

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	uint16 BaseHealth = 100;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	uint16 BaseMana = 100;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	uint16 BaseStamina = 100;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	uint16 BaseMoveSpeed = 200;
};

#pragma once
#include "ProjectH/Utils/MacroUtil.h"
#include "BossKaurgStruct.generated.h"

USTRUCT()
struct PROJECTH_API FBossKaurgCacheHandData
{
	GENERATED_USTRUCT_BODY()

	GETTER_REF(FVector, PrevHandPosition)
	SETTER(FVector, PrevHandPosition)
	GETTER_REF(FVector, PrevHandForwardVector)
	SETTER(FVector, PrevHandForwardVector)
	GETTER_REF(FVector, PrevHandUpVector)
	SETTER(FVector, PrevHandUpVector)

private:
	UPROPERTY()
	FVector PrevHandPosition = FVector::ZeroVector;

	UPROPERTY()
	FVector PrevHandForwardVector = FVector::ZeroVector;

	UPROPERTY()
	FVector PrevHandUpVector = FVector::ZeroVector;
};

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "ProjectH/Utils/MacroUtil.h"
#include "HorizonAbilitySystemInitializeData.generated.h"

class UGA_BaseAbility;

UCLASS()
class PROJECTH_API UHorizonAbilitySystemInitializeData : public UDataAsset
{
	GENERATED_BODY()

public:
	GETTER_REF(TArray<TSubclassOf<UGA_BaseAbility>>, DefaultGameplayAbilities)
	GETTER(FGameplayTagContainer,DefaultGameplayTags)

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<UGA_BaseAbility>> DefaultGameplayAbilities;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	FGameplayTagContainer DefaultGameplayTags;
};

#pragma once

#include "NativeGameplayTags.h"

struct FGameplayTag;
class UAbilitySystemComponent;

namespace HorizonGameplayTags
{
	PROJECTH_API void AddGameplayTag(UAbilitySystemComponent* ASC
									, const FGameplayTag Tag
									, const int32 Count = 1
									, const bool IsReplicated = false);

	PROJECTH_API void RemoveGameplayTag(UAbilitySystemComponent* ASC
										, const FGameplayTag Tag
										, const int32 Count = -1
										, const bool IsReplicated = false);

	PROJECTH_API void SetGameplayTag(UAbilitySystemComponent* ASC
									, const FGameplayTag Tag, const int32 Count
									, const bool IsReplicated = false);

	PROJECTH_API void SwapGameplayTag(UAbilitySystemComponent* ASC
									, const FGameplayTag FromTag
									, const FGameplayTag ToTag
									, const bool IsReplicated = false);

	PROJECTH_API uint32 GetGameplayTagCount(UAbilitySystemComponent* ASC
											, const FGameplayTag FindToTag);

	PROJECTH_API bool HasGameplayTag(UAbilitySystemComponent* ASC
									, const FGameplayTag FindToTag);

	PROJECTH_API void ToggleGameplayTag(UAbilitySystemComponent* ASC
										, const FGameplayTag Tag
										, const bool IsForceActive = false
										, const bool IsReplicated = false);

	PROJECTH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Test_Tag)
	PROJECTH_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Passive_Died)
}

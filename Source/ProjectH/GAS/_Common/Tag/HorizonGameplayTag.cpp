﻿#include "HorizonGameplayTag.h"

#include "AbilitySystemComponent.h"
#include "NativeGameplayTags.h"

namespace HorizonGameplayTags
{
	void AddGameplayTag(UAbilitySystemComponent* ASC, const FGameplayTag Tag
						, const int32 Count, const bool IsReplicated)
	{
		const uint32 CurrentTagCount = GetGameplayTagCount(ASC, Tag);

		if (IsReplicated)
		{
			ASC->SetReplicatedLooseGameplayTagCount(
				Tag, CurrentTagCount + Count);
		}

		ASC->SetLooseGameplayTagCount(Tag, CurrentTagCount + Count);
	}

	void RemoveGameplayTag(UAbilitySystemComponent* ASC, const FGameplayTag Tag
							, const int32 Count, const bool IsReplicated)
	{
		// Count가 -1 즉 기본 값으로 설정되어 있다면, 전부 없애기 위해 0으로 설정하고
		// 그게 아니라면 현재 갯수에서 N개만 빼게 설정한다.
		const int32 NewCount = Count == -1
									? 0
									: ASC->GetGameplayTagCount(Tag) - Count;

		if (IsReplicated)
		{
			ASC->SetReplicatedLooseGameplayTagCount(Tag, NewCount);
		}
		ASC->SetLooseGameplayTagCount(Tag, NewCount);
	}

	void SetGameplayTag(UAbilitySystemComponent* ASC, const FGameplayTag Tag
						, const int32 Count, const bool IsReplicated)
	{
		if (IsReplicated)
		{
			ASC->SetReplicatedLooseGameplayTagCount(Tag, Count);
		}
		ASC->SetLooseGameplayTagCount(Tag, Count);
	}

	void SwapGameplayTag(UAbilitySystemComponent* ASC
						, const FGameplayTag FromTag, const FGameplayTag ToTag
						, const bool IsReplicated)
	{
		const uint8 FromTagCount = ASC->GetGameplayTagCount(FromTag);
		RemoveGameplayTag(ASC, FromTag, FromTagCount, IsReplicated);
		AddGameplayTag(ASC, ToTag, FromTagCount, IsReplicated);
	}

	uint32 GetGameplayTagCount(UAbilitySystemComponent* ASC
								, const FGameplayTag FindToTag)
	{
		return ASC->GetGameplayTagCount(FindToTag);
	}

	bool HasGameplayTag(UAbilitySystemComponent* ASC
						, const FGameplayTag FindToTag)
	{
		return ASC->HasMatchingGameplayTag(FindToTag);
	}

	void ToggleGameplayTag(UAbilitySystemComponent* ASC, const FGameplayTag Tag
							, const bool IsForceActive, const bool IsReplicated)
	{
		const bool HasTag = ASC->HasMatchingGameplayTag(Tag);
		// 강제 태그 
		const uint32 TagCount = IsForceActive ? IsForceActive : !HasTag;

		SetGameplayTag(ASC, Tag, TagCount, IsReplicated);
	}

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test_Tag, "Test.Tag", "테스트용 노출 태그");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Passive_Died, "Passive.Died", "사망 시 시전되는 스킬")
	;
}

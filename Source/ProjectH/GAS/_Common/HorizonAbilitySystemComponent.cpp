#include "HorizonAbilitySystemComponent.h"
#include "HorizonAbilitySystemInitializeData.h"
#include "Ability/GA_BaseAbility.h"

UHorizonAbilitySystemComponent::UHorizonAbilitySystemComponent()
{
	ReplicationMode = EGameplayEffectReplicationMode::Mixed;
	SetIsReplicatedByDefault(true);
}

void UHorizonAbilitySystemComponent::Initialize(
	UHorizonAbilitySystemInitializeData* InitialData)
{
	if (!InitialData)
	{
		return;
	}

	if (GetIsInitialize())
	{
		return;
	}

	// Ability는 반드시 서버 환경에서만 Give Ability를 수행해야 한다.
	if (GetOwnerRole() != ROLE_Authority)
	{
		return;
	}
	
	if (!InitialData->GetDefaultGameplayAbilities().IsEmpty())
	{
		for (const TSubclassOf<UGA_BaseAbility> Ability : InitialData->GetDefaultGameplayAbilities())
		{
			UGA_BaseAbility* BaseAbility = Ability->
				GetDefaultObject<UGA_BaseAbility>();

			BaseAbility->InitializeAbility(this);
		}
	}
	
	if (!InitialData->GetDefaultGameplayTags().IsEmpty())
	{
		AddLooseGameplayTags(InitialData->GetDefaultGameplayTags());
	}

	SetIsInitialize(true);
}

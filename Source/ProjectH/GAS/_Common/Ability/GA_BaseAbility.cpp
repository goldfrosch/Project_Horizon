#include "GA_BaseAbility.h"

#include "ProjectH/GAS/_Common/HorizonAbilitySystemComponent.h"

bool UGA_BaseAbility::InitializeAbility(UHorizonAbilitySystemComponent* ASC)
{
	if (!IsInitialized)
	{
		ASC->GiveAbility(
			FGameplayAbilitySpec(this, GetAbilityLevel(), INDEX_NONE, ASC));
	}

	return IsInitialized;
}

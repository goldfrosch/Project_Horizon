#include "GA_BaseInputAbility.h"

#include "ProjectH/GAS/AbilitySystemEnum.h"
#include "ProjectH/GAS/_Common/HorizonAbilitySystemComponent.h"

bool UGA_BaseInputAbility::InitializeAbility(
	UHorizonAbilitySystemComponent* ASC)
{
	if (Super::InitializeAbility(ASC))
	{
		return true;
	}
	
	IsInitialized = true;

	const int32 NewInputId = GetInputId() == EAbilityInputId::Undefined
										? INDEX_NONE
										: static_cast<int32>(GetInputId());
				
	ASC->GiveAbility(FGameplayAbilitySpec(
		this, GetAbilityLevel(), NewInputId, ASC));
	
	return IsInitialized;
}

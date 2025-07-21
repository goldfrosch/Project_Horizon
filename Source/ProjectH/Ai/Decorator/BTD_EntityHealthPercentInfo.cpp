#include "BTD_EntityHealthPercentInfo.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "AIController.h"
#include "ProjectH/GAS/_Common/HorizonAbilitySystemComponent.h"
#include "ProjectH/GAS/_Common/Attribute/ATR_BaseAttribute.h"

UBTD_EntityHealthPercentInfo::UBTD_EntityHealthPercentInfo()
{
	NodeName = TEXT("Entity Health Percent Info");
}

bool UBTD_EntityHealthPercentInfo::CalculateRawConditionValue(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const AAIController* AIC = Cast<AAIController>(OwnerComp.GetOwner());

	UAbilitySystemComponent* AbilitySystemComponent =
		UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(
			AIC->GetPawn());

	if (!AbilitySystemComponent->IsValidLowLevel())
	{
		return false;
	}

	UHorizonAbilitySystemComponent* ASC = Cast<UHorizonAbilitySystemComponent>(
		AbilitySystemComponent);

	if (!ASC->IsValidLowLevel())
	{
		return false;
	}

	const UATR_BaseAttribute* AttributeSet = Cast<UATR_BaseAttribute>(
		ASC->GetAttributeSet(UATR_BaseAttribute::StaticClass()));

	UE_LOG(LogTemp, Display, TEXT("테스트: %f / %f"), AttributeSet->GetHealth()
			, AttributeSet->GetMaxHealth());

	const float RemainHealthPercent = AttributeSet->GetHealth() / AttributeSet->
		GetMaxHealth();
	const float ComparePercent = Percent / 100;

	switch (HealthPercentCalcType)
	{
	case EBTD_EntityHealthPercentCalcType::Equal:
		{
			if (RemainHealthPercent == ComparePercent)
			{
				return true;
			}
			return false;
		}
	case EBTD_EntityHealthPercentCalcType::Greater:
		{
			if (RemainHealthPercent >= ComparePercent)
			{
				return true;
			}
			return false;
		}
	case EBTD_EntityHealthPercentCalcType::Less:
		{
			if (RemainHealthPercent <= ComparePercent)
			{
				return true;
			}
			return false;
		}
	}

	return false;
}

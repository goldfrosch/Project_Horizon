#include "BTD_HasGameplayTag.h"
#include "AIController.h"
#include "ProjectH/Characters/BasePawn.h"
#include "ProjectH/GAS/_Common/Tag/HorizonGameplayTag.h"

UBTD_HasGameplayTag::UBTD_HasGameplayTag()
{
	NodeName = TEXT("Has Gameplay Tag");
}

bool UBTD_HasGameplayTag::CalculateRawConditionValue(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const AAIController* AIController = Cast<AAIController>(
		OwnerComp.GetOwner());
	if (!AIController->IsValidLowLevel())
	{
		return false;
	}

	const ABasePawn* OwnerPawn = Cast<ABasePawn>(AIController->GetPawn());
	if (!OwnerPawn->IsValidLowLevel())
	{
		return false;
	}

	const bool Result = HorizonGameplayTags::HasGameplayTag(
		OwnerPawn->GetAbilitySystemComponent(), Tag);

	return Super::CalculateRawConditionValue(OwnerComp, NodeMemory) && Result;
}

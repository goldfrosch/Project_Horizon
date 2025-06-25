#include "BTT_ActiveGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "ProjectH/Characters/BasePawn.h"
#include "ProjectH/GAS/_Common/Ability/GA_BaseAbility.h"

UBTT_ActiveGameplayAbility::UBTT_ActiveGameplayAbility()
{
	NodeName = TEXT("Active Gameplay Ability");
	bNotifyTick = false;
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTT_ActiveGameplayAbility::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AI = OwnerComp.GetAIOwner();
	if (!AI->IsValidLowLevel())
	{
		return EBTNodeResult::Failed;
	}

	CurrentOwnerComp = &OwnerComp;

	ABasePawn* BasePawn = Cast<ABasePawn>(AI->GetPawn());
	if (!BasePawn->IsValidLowLevel())
	{
		return EBTNodeResult::Failed;
	}

	UAbilitySystemComponent* ASC = BasePawn->GetAbilitySystemComponent();
	if (!ASC->IsValidLowLevel())
	{
		return EBTNodeResult::Failed;
	}

	TArray<FGameplayAbilitySpecHandle> OutAbilityHandles;
	FGameplayTagContainer FindTagContainer;
	FindTagContainer.AddTag(TargetSkillTag);

	ASC->FindAllAbilitiesWithTags(OutAbilityHandles, FindTagContainer);

	if (OutAbilityHandles.IsEmpty())
	{
		return EBTNodeResult::Failed;
	}

	// 찾은 첫번째 타겟 스킬을 가져다 활용함
	CurrentAbilityInstance = ASC->FindAbilitySpecFromHandle(
		OutAbilityHandles[0])->GetPrimaryInstance();

	if (!CurrentAbilityInstance->IsValidLowLevel())
	{
		return EBTNodeResult::Failed;
	}

	CurrentAbilityInstance->OnGameplayAbilityEnded.AddUObject(
		this, &ThisClass::OnAbilityEnd_Internal);
	CurrentAbilityInstance->OnGameplayAbilityCancelled.AddUObject(
		this, &ThisClass::OnAbilityCancel_Internal);

	if (!ASC->TryActivateAbilitiesByTag(FindTagContainer))
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTT_ActiveGameplayAbility::AbortTask(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!CurrentAbilityInstance->IsValidLowLevel())
	{
		return Super::AbortTask(OwnerComp, NodeMemory);
	}

	if (!CurrentAbilityInstance->IsActive())
	{
		return Super::AbortTask(OwnerComp, NodeMemory);
	}

	CurrentAbilityInstance->K2_CancelAbility();
	CurrentAbilityInstance = nullptr;

	return Super::AbortTask(OwnerComp, NodeMemory);
}

void UBTT_ActiveGameplayAbility::OnAbilityEnd_Internal(UGameplayAbility* Data)
{
	FinishLatentTask(*CurrentOwnerComp, EBTNodeResult::Succeeded);
}

void UBTT_ActiveGameplayAbility::OnAbilityCancel_Internal()
{
	FinishLatentTask(*CurrentOwnerComp, EBTNodeResult::Failed);
}

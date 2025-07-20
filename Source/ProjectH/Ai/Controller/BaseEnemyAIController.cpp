#include "BaseEnemyAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Navigation/CrowdFollowingComponent.h"


ABaseEnemyAIController::ABaseEnemyAIController(
	const FObjectInitializer& ObjectInitializer)
	: Super(
		ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(
			"Path Following Component"))
{
}

void ABaseEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!BehaviorTree->IsValidLowLevel())
	{
		return;
	}

	RunBehaviorTree(BehaviorTree);
}

ETeamAttitude::Type ABaseEnemyAIController::GetTeamAttitudeTowards(
	const AActor& Other) const
{
	const APawn* Target = Cast<const APawn>(&Other);
	const IGenericTeamAgentInterface* TargetTeamAgent = Cast<const
		IGenericTeamAgentInterface>(Target->GetController());

	if (!TargetTeamAgent)
	{
		return Super::GetTeamAttitudeTowards(Other);
	}

	if (TargetTeamAgent->GetGenericTeamId() != GetGenericTeamId())
	{
		return Super::GetTeamAttitudeTowards(Other);
	}

	return ETeamAttitude::Neutral;
}

void ABaseEnemyAIController::OnEnemyPerceptionUpdated(AActor* Actor
	, FAIStimulus Stimulus)
{
	if (!Actor->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Display, TEXT("타겟 없음"))
	}

	if (!Stimulus.WasSuccessfullySensed())
	{
		return;
	}

	if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
	{
		if (BlackboardComponent->GetValueAsObject("TargetActor") != Actor)
		{
			BlackboardComponent->SetValueAsObject("TargetActor", Actor);
		}
	}
}

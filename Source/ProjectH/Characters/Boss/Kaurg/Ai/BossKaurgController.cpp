#include "BossKaurgController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

ABossKaurgController::ABossKaurgController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABossKaurgController::BeginPlay()
{
	Super::BeginPlay();

	if (!BehaviorTree->IsValidLowLevel())
	{
		return;
	}

	RunBehaviorTree(BehaviorTree);

	GetBlackboardComponent()->SetValueAsInt(TEXT("ComboIndex"), 0);
}

void ABossKaurgController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

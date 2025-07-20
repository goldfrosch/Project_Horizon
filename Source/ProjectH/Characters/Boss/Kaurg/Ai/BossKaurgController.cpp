#include "BossKaurgController.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ABossKaurgController::ABossKaurgController(
	const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	EnemySenseSightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(
		"AI Sense Config Sight");
	EnemySenseSightConfig->DetectionByAffiliation.bDetectEnemies = true;
	EnemySenseSightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	EnemySenseSightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	EnemySenseSightConfig->SightRadius = 5000.f;
	EnemySenseSightConfig->LoseSightRadius = 0.f;
	EnemySenseSightConfig->PeripheralVisionAngleDegrees = 360.f;


	EnemyPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(
		"Enemy Perception Component");
	EnemyPerceptionComponent->ConfigureSense(*EnemySenseSightConfig);
	EnemyPerceptionComponent->SetDominantSense(
		UAISenseConfig_Sight::StaticClass());
	EnemyPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(
		this, &ThisClass::OnEnemyPerceptionUpdated);
}

void ABossKaurgController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	// GetBlackboardComponent()->SetValueAsInt(TEXT("ComboIndex"), 0);
}

void ABossKaurgController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

#pragma once

#include "CoreMinimal.h"
#include "ProjectH/Ai/Controller/BaseEnemyAIController.h"
#include "BossKaurgController.generated.h"

UCLASS()
class PROJECTH_API ABossKaurgController : public ABaseEnemyAIController
{
	GENERATED_BODY()

public:
	ABossKaurgController(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;
};

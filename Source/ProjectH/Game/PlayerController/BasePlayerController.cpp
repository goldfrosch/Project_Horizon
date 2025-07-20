#include "BasePlayerController.h"

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	TeamId = FGenericTeamId(0);
}

FGenericTeamId ABasePlayerController::GetGenericTeamId() const
{
	return TeamId;
}

#include "BasePlayerController.h"

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	ConsoleCommand("showdebug AbilitySystem");
}

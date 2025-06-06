#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"


APlayerCharacter::APlayerCharacter()
{
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void APlayerCharacter::SetupPlayerInputComponent(
	UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<
		UEnhancedInputComponent>(PlayerInputComponent);
	
	if (!EnhancedInputComponent)
	{
		return;
	}
	
	OnInputBindingNotified.Broadcast(EnhancedInputComponent);
}

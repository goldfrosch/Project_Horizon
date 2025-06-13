#include "BaseCharacterAnimInstance.h"

#include "Player/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBaseCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Player = Cast<APlayerCharacter>(GetOwningActor());
	if (!Player)
	{
		return;
	}

	MovementComponent = Player->GetCharacterMovement();
}

void UBaseCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Player || !MovementComponent)
	{
		return;
	}

	GroundSpeed_H = FVector::DotProduct(Player->GetVelocity()
										, Player->GetActorRightVector());
	GroundSpeed_V = FVector::DotProduct(Player->GetVelocity()
										, Player->GetActorForwardVector());

	if (GroundSpeed_H != 0 || GroundSpeed_V != 0)
	{
		bShouldMove = MovementComponent->GetCurrentAcceleration() !=
			FVector::ZeroVector;
	}

	bIsFalling = MovementComponent->IsFalling();
}

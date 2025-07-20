#include "BossKaurgAnimInstance.h"

#include "GameFramework/FloatingPawnMovement.h"
#include "ProjectH/Characters/BasePawn.h"

void UBossKaurgAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ABasePawn* Pawn = Cast<ABasePawn>(TryGetPawnOwner());
	if (!Pawn)
	{
		IsInAir = false;
		return;
	}

	Velocity = Pawn->GetFloatingPawnMovement()->Velocity * DeltaSeconds;
	MoveToVelocity = Velocity.GetSafeNormal();
	IsInAir = Pawn->GetIsInAir();
}

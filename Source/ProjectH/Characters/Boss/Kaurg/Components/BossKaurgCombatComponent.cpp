#include "BossKaurgCombatComponent.h"

#include "Components/BoxComponent.h"


UBossKaurgCombatComponent::UBossKaurgCombatComponent()
{
}


void UBossKaurgCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBossKaurgCombatComponent::CaptureRightHandPosition()
{
	SetPrevRightHandPosition(
		GetRightHandAttackRegion()->GetComponentLocation());
	SetPrevRightHandForce(GetRightHandAttackRegion()->GetForwardVector());
}

void UBossKaurgCombatComponent::CaptureLeftHandPosition()
{
	SetPrevLeftHandPosition(GetLeftHandAttackRegion()->GetComponentLocation());
	SetPrevLeftHandForce(GetLeftHandAttackRegion()->GetForwardVector());
}

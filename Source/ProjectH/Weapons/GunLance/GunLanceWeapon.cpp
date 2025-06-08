#include "GunLanceWeapon.h"

AGunLanceWeapon::AGunLanceWeapon()
{
}

void AGunLanceWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AGunLanceWeapon::EquipWeapon(AActor* NewOwner)
{
	Super::EquipWeapon(NewOwner);

	GunLance->AttachToComponent(NewOwner->GetRootComponent(),
		FAttachmentTransformRules::SnapToTargetNotIncludingScale, "hand_lSocket");
	Shield->AttachToComponent(NewOwner->GetRootComponent(),
		FAttachmentTransformRules::SnapToTargetNotIncludingScale, "hand_rSocket");
}


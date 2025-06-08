#pragma once

#include "CoreMinimal.h"
#include "ProjectH/Weapons/BaseWeapon.h"
#include "GunLanceWeapon.generated.h"

UCLASS()
class PROJECTH_API AGunLanceWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:
	AGunLanceWeapon();

	virtual void EquipWeapon(AActor* NewOwner) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Options|Weapon", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> GunLance;
	
	UPROPERTY(EditDefaultsOnly, Category = "Options|Weapon", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> Shield;
};

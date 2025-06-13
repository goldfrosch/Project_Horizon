#pragma once

#include "CoreMinimal.h"
#include "ProjectH/Characters/BasePawn.h"
#include "BossKaurg.generated.h"

class UBossKaurgCombatComponent;
class UBoxComponent;

UCLASS()
class PROJECTH_API ABossKaurg : public ABasePawn
{
	GENERATED_BODY()

public:
	ABossKaurg();

	GETTER(TObjectPtr<UBossKaurgCombatComponent>, BossKaurgCombatComponent)

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> CollisionBox;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UBossKaurgCombatComponent> BossKaurgCombatComponent;
};

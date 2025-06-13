#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectH/Utils/MacroUtil.h"
#include "BossKaurgCombatComponent.generated.h"


class UBoxComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTH_API UBossKaurgCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBossKaurgCombatComponent();

	GETTER_EDITABLE(TObjectPtr<UBoxComponent>, RightHandAttackRegion)
	SETTER(TObjectPtr<UBoxComponent>, RightHandAttackRegion)
	GETTER_SETTER(FVector, PrevRightHandPosition)

	GETTER_EDITABLE(TObjectPtr<UBoxComponent>, LeftHandAttackRegion)
	SETTER(TObjectPtr<UBoxComponent>, LeftHandAttackRegion)
	GETTER_SETTER(FVector, PrevLeftHandPosition)

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> RightHandAttackRegion;

	UPROPERTY()
	FVector PrevRightHandPosition;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> LeftHandAttackRegion;

	UPROPERTY()
	FVector PrevLeftHandPosition;
};

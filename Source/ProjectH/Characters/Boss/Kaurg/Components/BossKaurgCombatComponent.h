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
	GETTER_SETTER(FVector, PrevRightHandForce)

	GETTER_EDITABLE(TObjectPtr<UBoxComponent>, LeftHandAttackRegion)
	SETTER(TObjectPtr<UBoxComponent>, LeftHandAttackRegion)
	GETTER_SETTER(FVector, PrevLeftHandPosition)
	GETTER_SETTER(FVector, PrevLeftHandForce)

	void CaptureRightHandPosition();
	void CaptureLeftHandPosition();

protected:
	virtual void BeginPlay() override;

private:
#pragma region RightHand
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> RightHandAttackRegion;

	UPROPERTY()
	FVector PrevRightHandPosition = FVector::ZeroVector;

	UPROPERTY()
	FVector PrevRightHandForce = FVector::ZeroVector;
#pragma endregion

#pragma region LeftHand
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> LeftHandAttackRegion;

	UPROPERTY()
	FVector PrevLeftHandPosition = FVector::ZeroVector;

	UPROPERTY()
	FVector PrevLeftHandForce = FVector::ZeroVector;
#pragma endregion
};

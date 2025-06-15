#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectH/Utils/MacroUtil.h"
#include "BossKaurgCombatComponent.generated.h"

class UBoxComponent;

struct FSquareTraceParams;

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
	GETTER_SETTER(FVector, PrevRightHandUpVector)

	GETTER_EDITABLE(TObjectPtr<UBoxComponent>, LeftHandAttackRegion)
	SETTER(TObjectPtr<UBoxComponent>, LeftHandAttackRegion)
	GETTER_SETTER(FVector, PrevLeftHandPosition)
	GETTER_SETTER(FVector, PrevLeftHandForce)
	GETTER_SETTER(FVector, PrevLeftHandUpVector)

	// TODO: Trace 관련은 Ability로 이전하는 것을 고려하기
	void TraceToAttackLeftHand();
	void TraceToAttackRightHand();

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

	UPROPERTY()
	FVector PrevRightHandUpVector = FVector::ZeroVector;
#pragma endregion

#pragma region LeftHand
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> LeftHandAttackRegion;

	UPROPERTY()
	FVector PrevLeftHandPosition = FVector::ZeroVector;

	UPROPERTY()
	FVector PrevLeftHandForce = FVector::ZeroVector;

	UPROPERTY()
	FVector PrevLeftHandUpVector = FVector::ZeroVector;
#pragma endregion

	float LagDistance = 40.f;

	void TraceAttackPosition_Internal(FSquareTraceParams& TraceParams
									, const FVector& P0, const FVector& P1
									, const FVector& P2, const bool IsLeft);

	void OnTraceAttackHit_Internal();

	UPROPERTY()
	TArray<AActor*> IgnoreActors;

	TArray<FHitResult> HitResults;
};

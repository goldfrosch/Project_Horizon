#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectH/Utils/MacroUtil.h"
#include "ProjectH/Characters/Boss/Kaurg/BossKaurgStruct.h"
#include "BossKaurgCombatComponent.generated.h"

enum class EBossKaurgHandType : uint8;
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

	GETTER_EDITABLE(TObjectPtr<UBoxComponent>, LeftHandAttackRegion)
	SETTER(TObjectPtr<UBoxComponent>, LeftHandAttackRegion)

	// TODO: Trace 관련은 Ability로 이전하는 것을 고려하기
	void TraceToAttackLeftHand();
	void TraceToAttackRightHand();

	void CaptureRightHandPosition();
	void CaptureLeftHandPosition();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TMap<EBossKaurgHandType, FBossKaurgCacheHandData> BossHandCacheData;

	UPROPERTY()
	TMap<EBossKaurgHandType, TObjectPtr<UBoxComponent>> CurrentBossHandBox;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> RightHandAttackRegion;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> LeftHandAttackRegion;

	float LagDistance = 40.f;

	void TraceAttackPosition_Internal(FSquareTraceParams& TraceParams
									, const FVector& P0, const FVector& P1
									, const FVector& P2
									, const EBossKaurgHandType HandType);

	void OnTraceAttackHit_Internal();

	UPROPERTY()
	TArray<AActor*> IgnoreActors;

	TArray<FHitResult> HitResults;
};

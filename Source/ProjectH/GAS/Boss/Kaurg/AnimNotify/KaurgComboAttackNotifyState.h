#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "KaurgComboAttackNotifyState.generated.h"

class UBoxComponent;

UCLASS()
class PROJECTH_API UKaurgComboAttackNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp
							, UAnimSequenceBase* Animation, float TotalDuration
							, const FAnimNotifyEventReference&
							EventReference) override;

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp
							, UAnimSequenceBase* Animation, float FrameDeltaTime
							, const FAnimNotifyEventReference&
							EventReference) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp
							, UAnimSequenceBase* Animation
							, const FAnimNotifyEventReference&
							EventReference) override;

private:
	UPROPERTY(EditInstanceOnly, Category = "Options"
		, meta = (AllowPrivateAccess = true))
	bool IsLeftEnabled;

	UPROPERTY(EditInstanceOnly, Category = "Options"
		, meta = (AllowPrivateAccess = true))
	bool IsRightEnabled;

	FVector GetForwardVectorByBox(const UBoxComponent* Box);

	void DebugAttackPosition(const UWorld* World, const FVector& P0
							, const FVector& P1, const FVector& P2
							, const UBoxComponent* AttackBox);

	// 이 거리보다 더 큰 경우 렉 처럼 판단해 위치 보간을 수행해준다.
	float LagDistance = 20.f;
};

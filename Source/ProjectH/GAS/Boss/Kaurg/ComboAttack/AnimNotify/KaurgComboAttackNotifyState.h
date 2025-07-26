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
};

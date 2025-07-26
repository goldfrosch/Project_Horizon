#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_PawnMotionWarping.generated.h"

UCLASS()
class PAWNMOTIONWARPING_API UANS_PawnMotionWarping : public UAnimNotifyState
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
	UPROPERTY(EditInstanceOnly, Category = "Config|Warp"
		, meta = (AllowPrivateAccess = true))
	FName WarpName;

	UPROPERTY(EditInstanceOnly, Category = "Config|Warp"
		, meta = (AllowPrivateAccess = true))
	EAlphaBlendOption WarpingCurve;
};

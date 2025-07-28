#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_KaurgLeapingCrushCollision.generated.h"

UCLASS()
class PROJECTH_API UANS_KaurgLeapingCrushCollision : public UAnimNotifyState
{
	GENERATED_BODY()

protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp
							, UAnimSequenceBase* Animation, float TotalDuration
							, const FAnimNotifyEventReference&
							EventReference) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp
							, UAnimSequenceBase* Animation
							, const FAnimNotifyEventReference&
							EventReference) override;
};

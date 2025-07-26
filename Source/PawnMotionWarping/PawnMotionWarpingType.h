#pragma once

#include "AlphaBlend.h"
#include "PawnMotionWarpingType.generated.h"

USTRUCT(BlueprintType)
struct PAWNMOTIONWARPING_API FPawnMotionWarpingNotifyStateData
{
	GENERATED_USTRUCT_BODY()

	EAlphaBlendOption GetEasingCurve() const
	{
		return EasingCurve;
	}

private:
	UPROPERTY(EditInstanceOnly, meta = (AllowPrivateAccess = true))
	EAlphaBlendOption EasingCurve = EAlphaBlendOption::Linear;
};

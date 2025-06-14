#pragma once

class FMathUtil
{
public:
	static FVector GetMiddlePoint(const FVector& Start, const FVector& End
								, const float Percent = 0.5)
	{
		return (Start + End) * Percent;
	}

	static FVector GetBezierPoint(const FVector& P0, const FVector& P1
								, const FVector& P2, const float T)
	{
		return FMath::Pow(1.0f - T, 2) * P0 + 2 * (1.0f - T) * T * P1 +
			FMath::Pow(T, 2) * P2;
	}
};

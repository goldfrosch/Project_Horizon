#pragma once

class FMathUtil
{
public:
	static FVector GetBezierControlPointByVectors(
		const FVector& Start, const FVector& End, const float Height)
	{
		const FVector MidPoint = (Start + End) * 0.5f;
		const float Distance = FVector::Distance(Start, End);

		const float AdaptiveHeight = Distance * Height;

		const FVector Direction = (End - Start).GetSafeNormal();

		return MidPoint + Direction.UpVector * AdaptiveHeight;
	}

	static FVector GetBezierPoint(const FVector& P0, const FVector& P1
								, const FVector& P2, const float T)
	{
		return FMath::Pow(1 - T, 2) * P0 + 2 * (1 - T) * T * P1 +
			FMath::Pow(T, 2) * P2;
	}
};

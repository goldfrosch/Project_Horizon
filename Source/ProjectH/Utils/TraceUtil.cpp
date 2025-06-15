#include "TraceUtil.h"

#include "Kismet/KismetSystemLibrary.h"

TArray<FVector> FTraceUtil::SquareScalePointArray = {
	{-1, -1, 0}, {-1, 1, 0}, {1, -1, 0}, {1, 1, 0}, {0, 0, 0}
};

void FTraceUtil::BoxTraceMulti(FBoxTraceParams& TraceParams
								, TArray<AActor*>& IgnoreActors
								, TArray<FHitResult>& HitResults)
{
}

void FTraceUtil::SquareTraceMulti(FSquareTraceParams& TraceParams
								, TArray<AActor*>& IgnoreActors
								, TArray<FHitResult>& HitResults)
{
	for (const FVector& ScalePinPoint : SquareScalePointArray)
	{
		const FVector PinPoint = GetSquarePositionValueWithScalePoint(
			TraceParams, ScalePinPoint);

		if (TraceParams.IsShowDebugTrace)
		{
			UKismetSystemLibrary::DrawDebugSphere(TraceParams.World
												, PinPoint, 2, 12
												, FLinearColor::Yellow, 1, 1);
		}
	}

	LineTraceBySquareScalePoint(TraceParams, 0, 1, IgnoreActors, HitResults);
	LineTraceBySquareScalePoint(TraceParams, 2, 3, IgnoreActors, HitResults);
	LineTraceBySquareScalePoint(TraceParams, 1, 3, IgnoreActors, HitResults);
	LineTraceBySquareScalePoint(TraceParams, 0, 2, IgnoreActors, HitResults);
	LineTraceBySquareScalePoint(TraceParams, 2, 1, IgnoreActors, HitResults);
	LineTraceBySquareScalePoint(TraceParams, 0, 3, IgnoreActors, HitResults);
}

FVector FTraceUtil::GetSquarePositionValueWithScalePoint(
	const FSquareTraceParams& Params, const FVector& Scale)
{
	FVector PinPoint = Params.SquareInfo.Position;
	PinPoint += Params.SquareInfo.ForwardVector * Scale.X * Params.SquareExtents
		.X;
	PinPoint += FVector::CrossProduct(Params.SquareInfo.ForwardVector
									, Params.SquareInfo.UpVector) * Scale.Y *
		Params.SquareExtents.Y;

	return PinPoint;
}

void FTraceUtil::LineTraceBySquareScalePoint(FSquareTraceParams& Params
											, const uint8 P0, const uint8 P1
											, TArray<AActor*>& IgnoreActors
											, TArray<FHitResult>& HitResults)
{
	UKismetSystemLibrary::LineTraceMulti(Params.World
										, GetSquarePositionValueWithScalePoint(
											Params, SquareScalePointArray[P0])
										, GetSquarePositionValueWithScalePoint(
											Params, SquareScalePointArray[P1])
										, TraceTypeQuery1, false, IgnoreActors
										, Params.IsShowDebugTrace
											? EDrawDebugTrace::ForDuration
											: EDrawDebugTrace::None, HitResults
										, true, FLinearColor::Red
										, FLinearColor::Green, 1);
}

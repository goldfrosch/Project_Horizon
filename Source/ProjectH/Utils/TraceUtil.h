#pragma once

struct PROJECTH_API FSquareInfoParams
{
	FVector UpVector;
	FVector ForwardVector;
	FVector Position;
};

struct PROJECTH_API FTraceParams
{
	const UWorld* World;
	TArray<AActor*> IgnoreActors;
	TArray<FHitResult> HitResults;

	bool IsShowDebugTrace;
};

struct PROJECTH_API FSquareTraceParams : FTraceParams
{
	FVector SquareExtents;

	FSquareInfoParams SquareInfo;
};

struct PROJECTH_API FBoxTraceParams : FTraceParams
{
	FVector BoxExtents;

	FSquareInfoParams StartSquareInfo;
	FSquareInfoParams EndSquareInfo;
};

class FTraceUtil
{
public:
	static void BoxTraceMulti(FBoxTraceParams& TraceParams);
	static void SquareTraceMulti(FSquareTraceParams& TraceParams);

private:
	static TArray<FVector> SquareScalePointArray;

	static FVector GetSquarePositionValueWithScalePoint(
		const FSquareTraceParams& Params, const FVector& Scale);

	static void LineTraceBySquareScalePoint(FSquareTraceParams& Params
											, const uint8 P0, const uint8 P1);
};

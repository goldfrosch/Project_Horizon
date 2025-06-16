#pragma once

struct PROJECTH_API FSquareInfoParams
{
	FVector UpVector;
	FVector ForwardVector;
	FVector Position;
};

struct PROJECTH_API FTraceParams
{
	const UWorld* World = nullptr;

	bool IsShowDebugTrace = false;
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

	// 박스 Trace 시 바닥은 제거할 지
	bool IsRemovePlane;
};

class FTraceUtil
{
public:
	static void BoxTraceMulti(FBoxTraceParams& TraceParams
							, TArray<AActor*>& IgnoreActors
							, TArray<FHitResult>& HitResults);
	static void SquareTraceMulti(FSquareTraceParams& TraceParams
								, TArray<AActor*>& IgnoreActors
								, TArray<FHitResult>& HitResults);

private:
	static TArray<FVector> SquareScalePointArray;

	static FVector GetSquarePositionValueWithScalePoint(
		const FSquareTraceParams& Params, const FVector& Scale);

	static void LineTraceBySquareScalePoint(FSquareTraceParams& Params
											, const uint8 P0, const uint8 P1
											, TArray<AActor*>& IgnoreActors
											, TArray<FHitResult>& HitResults);

	static void LineTraceByBoxBridge(const FSquareTraceParams& StartSquareParams
									, const FSquareTraceParams& EndSquareParams
									, TArray<AActor*>& IgnoreActors
									, TArray<FHitResult>& HitResults);
};

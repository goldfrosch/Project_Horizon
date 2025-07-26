#pragma once

#include "CoreMinimal.h"
#include "PawnMotionWarping/PawnMotionWarpingType.h"

#include "PawnMotionWarpingComponent.generated.h"

struct PAWNMOTIONWARPING_API FPawnMotionWarpingSavedData
{
	FTransform Transform;
	float CurrentDuration;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PAWNMOTIONWARPING_API UPawnMotionWarpingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPawnMotionWarpingComponent();

	void AddMotionWarpingTransformData(const FName& MotionName
										, const FTransform& Transform);

	void AddMotionWarpingLocationAndRotationData(const FName& MotionName
												, const FVector& Location
												, const FRotator& Rotator);

	void SelectMotionWarping(const FName& MotionName, const float Duration = 0);

	bool IsMotionWarping();

	void UpdateBlendMotion(const float DeltaTime);

protected:
	virtual void BeginPlay() override;

private:
	TMap<FName, FPawnMotionWarpingSavedData> MotionWarpingData;

	FName CurrentMotionWarpingName = NAME_None;

	FPawnMotionWarpingNotifyStateData MotionWarpingNotifyStateData;

	FAlphaBlend AlphaBlend;
};

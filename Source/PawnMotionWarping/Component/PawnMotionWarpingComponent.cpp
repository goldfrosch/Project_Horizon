#include "PawnMotionWarpingComponent.h"


UPawnMotionWarpingComponent::UPawnMotionWarpingComponent()
{
}

void UPawnMotionWarpingComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPawnMotionWarpingComponent::SelectMotionWarping(
	const FName& MotionName, const float Duration)
{
	CurrentMotionWarpingName = MotionName;

	if (MotionName == NAME_None)
	{
		return;
	}

	MotionWarpingData[CurrentMotionWarpingName].CurrentDuration = 0.f;

	AlphaBlend.SetBlendTime(Duration);
	AlphaBlend.SetBlendOption(MotionWarpingNotifyStateData.GetEasingCurve());
	AlphaBlend.Reset();
}

void UPawnMotionWarpingComponent::AddMotionWarpingTransformData(
	const FName& MotionName, const FTransform& Transform)
{
	if (MotionWarpingData.Contains(MotionName))
	{
		MotionWarpingData[MotionName] = {Transform};
		return;
	}

	MotionWarpingData.Add(MotionName, {Transform});
}

void UPawnMotionWarpingComponent::AddMotionWarpingLocationAndRotationData(
	const FName& MotionName, const FVector& Location, const FRotator& Rotator)
{
	FTransform NewTransform;
	NewTransform.SetLocation(Location);
	NewTransform.SetRotation(Rotator.Quaternion());
	NewTransform.SetScale3D({1, 1, 1});

	if (MotionWarpingData.Contains(MotionName))
	{
		MotionWarpingData[MotionName].Transform = NewTransform;
		return;
	}

	MotionWarpingData.Add(MotionName, {NewTransform});
}

bool UPawnMotionWarpingComponent::IsMotionWarping()
{
	return CurrentMotionWarpingName != NAME_None;
}

void UPawnMotionWarpingComponent::UpdateBlendMotion(const float DeltaTime)
{
	if (!IsMotionWarping())
	{
		return;
	}

	MotionWarpingData[CurrentMotionWarpingName].CurrentDuration += DeltaTime;

	AlphaBlend.SetAlpha(
		MotionWarpingData[CurrentMotionWarpingName].CurrentDuration / AlphaBlend
		.GetBlendTime());

	UE_LOG(LogTemp, Display, TEXT("테스트: %f / %f")
			, MotionWarpingData[CurrentMotionWarpingName].CurrentDuration
			, AlphaBlend .GetBlendTime());

	FTransform UpdatedBlend;
	UpdatedBlend.Blend(GetOwner()->GetTransform()
						, MotionWarpingData[CurrentMotionWarpingName].Transform
						, AlphaBlend.GetAlpha());

	UpdatedBlend.SetLocation(
		UpdatedBlend.GetLocation() - GetOwner()->GetActorLocation());

	GetOwner()->AddActorWorldOffset(UpdatedBlend.GetLocation(), true);
	GetOwner()->SetActorRotation(UpdatedBlend.GetRotation().Rotator());
	GetOwner()->SetActorScale3D(UpdatedBlend.GetScale3D());
}

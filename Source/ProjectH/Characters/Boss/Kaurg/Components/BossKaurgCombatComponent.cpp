#include "BossKaurgCombatComponent.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ProjectH/Utils/MathUtil.h"
#include "ProjectH/Utils/TraceUtil.h"


UBossKaurgCombatComponent::UBossKaurgCombatComponent()
{
}


void UBossKaurgCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	IgnoreActors.Add(GetOwner());
}

void UBossKaurgCombatComponent::TraceToAttackLeftHand()
{
	const FVector PrevLeftLocation = GetPrevLeftHandPosition();
	const FVector NextLeftLocation = GetLeftHandAttackRegion()->
		GetComponentLocation();

	const FVector MidForceVector = (GetPrevLeftHandForce() +
		GetLeftHandAttackRegion()->GetForwardVector()) / 2;

	const FVector BezierMidPoint = FMathUtil::GetMiddlePoint(
		PrevLeftLocation, NextLeftLocation) + MidForceVector * FVector::Dist(
		PrevLeftLocation, NextLeftLocation) / LagDistance;

	TraceAttackPosition_Internal(GetWorld(), PrevLeftLocation, BezierMidPoint
								, NextLeftLocation, GetLeftHandAttackRegion());

	CaptureLeftHandPosition();
}

void UBossKaurgCombatComponent::TraceToAttackRightHand()
{
	const FVector PrevRightLocation = GetPrevRightHandPosition();
	const FVector NextRightLocation = GetRightHandAttackRegion()->
		GetComponentLocation();

	const FVector MidForceVector = (GetPrevRightHandForce() +
		GetRightHandAttackRegion()->GetForwardVector()) / 2;

	const FVector BezierMidPoint = FMathUtil::GetMiddlePoint(
		PrevRightLocation, NextRightLocation) + MidForceVector * FVector::Dist(
		PrevRightLocation, NextRightLocation) / LagDistance;

	TraceAttackPosition_Internal(GetWorld(), PrevRightLocation, BezierMidPoint
								, NextRightLocation
								, GetRightHandAttackRegion());

	CaptureRightHandPosition();
}

void UBossKaurgCombatComponent::CaptureRightHandPosition()
{
	SetPrevRightHandPosition(
		GetRightHandAttackRegion()->GetComponentLocation());
	SetPrevRightHandForce(GetRightHandAttackRegion()->GetForwardVector());
}

void UBossKaurgCombatComponent::CaptureLeftHandPosition()
{
	SetPrevLeftHandPosition(GetLeftHandAttackRegion()->GetComponentLocation());
	SetPrevLeftHandForce(GetLeftHandAttackRegion()->GetForwardVector());
}

void UBossKaurgCombatComponent::TraceAttackPosition_Internal(const UWorld* World
	, const FVector& P0, const FVector& P1, const FVector& P2
	, const UBoxComponent* AttackBox)
{
	const float Distance = FVector::Dist(P0, P2);
	// 보간 갯수
	const uint16 InterpCount = FMath::CeilToInt(
		FMath::Abs(Distance) / LagDistance);

	UKismetSystemLibrary::DrawDebugLine(World, P0, P2, FLinearColor::Red, 1, 1);

	FSquareTraceParams TraceParams;
	TraceParams.World = World;
	TraceParams.IgnoreActors = IgnoreActors;
	TraceParams.HitResults = HitResults;

	TraceParams.IsShowDebugTrace = true;
	TraceParams.SquareExtents = AttackBox->GetScaledBoxExtent();

	for (int i = 0; i <= InterpCount; i++)
	{
		const float Percent = InterpCount == 0
								? 1
								: i / static_cast<float>(InterpCount);

		const FVector BezierPoint = FMathUtil::GetBezierPoint(
			P0, P1, P2, Percent);

		TraceParams.SquareInfo.Position = BezierPoint;
		TraceParams.SquareInfo.ForwardVector = AttackBox->GetForwardVector();
		TraceParams.SquareInfo.UpVector = AttackBox->GetUpVector();

		FTraceUtil::SquareTraceMulti(TraceParams);
		OnTraceAttackHit_Internal();
	}
}

void UBossKaurgCombatComponent::OnTraceAttackHit_Internal()
{
	if (HitResults.Num() == 0)
	{
		return;
	}

	for (FHitResult& HitResult : HitResults)
	{
		if (IgnoreActors.Contains(HitResult.GetActor()))
		{
			continue;
		}

		IgnoreActors.Add(HitResult.GetActor());

		// TODO: 피격 관련 Ability 실행하기
	}
}

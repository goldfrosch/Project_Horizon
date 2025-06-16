#include "BossKaurgCombatComponent.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ProjectH/Characters/Boss/Kaurg/BossKaurgEnum.h"
#include "ProjectH/Characters/Boss/Kaurg/BossKaurgStruct.h"
#include "ProjectH/Utils/MathUtil.h"
#include "ProjectH/Utils/TraceUtil.h"


UBossKaurgCombatComponent::UBossKaurgCombatComponent()
{
}


void UBossKaurgCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	IgnoreActors.Add(GetOwner());

	BossHandCacheData.Add(EBossKaurgHandType::Left, FBossKaurgCacheHandData());
	BossHandCacheData.Add(EBossKaurgHandType::Right, FBossKaurgCacheHandData());

	CurrentBossHandBox.Add(EBossKaurgHandType::Left, GetLeftHandAttackRegion());
	CurrentBossHandBox.Add(EBossKaurgHandType::Right
							, GetRightHandAttackRegion());
}

void UBossKaurgCombatComponent::TraceToAttackLeftHand()
{
	const FVector PrevLeftLocation = BossHandCacheData[EBossKaurgHandType::Left]
		.GetPrevHandPosition();
	const FVector NextLeftLocation = GetLeftHandAttackRegion()->
		GetComponentLocation();

	const FVector MidForceVector = (BossHandCacheData[EBossKaurgHandType::Left].
		GetPrevHandForwardVector() + GetLeftHandAttackRegion()->
		GetForwardVector()) / 2;

	const FVector BezierMidPoint = FMathUtil::GetMiddlePoint(
		PrevLeftLocation, NextLeftLocation) + MidForceVector * FVector::Dist(
		PrevLeftLocation, NextLeftLocation) / LagDistance;

	FSquareTraceParams TraceParams;
	TraceParams.World = GetWorld();
	TraceParams.IsShowDebugTrace = true;
	TraceParams.SquareExtents = GetLeftHandAttackRegion()->GetScaledBoxExtent();

	TraceAttackPosition_Internal(TraceParams, PrevLeftLocation, BezierMidPoint
								, NextLeftLocation, EBossKaurgHandType::Left);

	CaptureLeftHandPosition();
}

void UBossKaurgCombatComponent::TraceToAttackRightHand()
{
	const FVector PrevRightLocation = BossHandCacheData[
		EBossKaurgHandType::Right].GetPrevHandPosition();
	const FVector NextRightLocation = GetRightHandAttackRegion()->
		GetComponentLocation();

	const FVector MidForceVector = (BossHandCacheData[EBossKaurgHandType::Right]
		.GetPrevHandForwardVector() + GetRightHandAttackRegion()->
		GetForwardVector()) / 2;

	const FVector BezierMidPoint = FMathUtil::GetMiddlePoint(
		PrevRightLocation, NextRightLocation) + MidForceVector * FVector::Dist(
		PrevRightLocation, NextRightLocation) / LagDistance;

	FSquareTraceParams TraceParams;
	TraceParams.World = GetWorld();
	TraceParams.IsShowDebugTrace = true;
	TraceParams.SquareExtents = GetRightHandAttackRegion()->
		GetScaledBoxExtent();

	TraceAttackPosition_Internal(TraceParams, PrevRightLocation, BezierMidPoint
								, NextRightLocation, EBossKaurgHandType::Right);

	CaptureRightHandPosition();
}

void UBossKaurgCombatComponent::CaptureRightHandPosition()
{
	BossHandCacheData[EBossKaurgHandType::Right].SetPrevHandPosition(
		GetRightHandAttackRegion()->GetComponentLocation());
	BossHandCacheData[EBossKaurgHandType::Right].SetPrevHandForwardVector(
		GetRightHandAttackRegion()->GetForwardVector());
	BossHandCacheData[EBossKaurgHandType::Right].SetPrevHandUpVector(
		GetRightHandAttackRegion()->GetUpVector());
}

void UBossKaurgCombatComponent::CaptureLeftHandPosition()
{
	BossHandCacheData[EBossKaurgHandType::Left].SetPrevHandPosition(
		GetLeftHandAttackRegion()->GetComponentLocation());
	BossHandCacheData[EBossKaurgHandType::Left].SetPrevHandForwardVector(
		GetLeftHandAttackRegion()->GetForwardVector());
	BossHandCacheData[EBossKaurgHandType::Left].SetPrevHandUpVector(
		GetLeftHandAttackRegion()->GetUpVector());
}

void UBossKaurgCombatComponent::TraceAttackPosition_Internal(
	FSquareTraceParams& TraceParams, const FVector& P0, const FVector& P1
	, const FVector& P2, const EBossKaurgHandType HandType)
{
	const float Distance = FVector::Dist(P0, P2);
	// 보간 갯수
	const uint16 InterpCount = FMath::CeilToInt(
		FMath::Abs(Distance) / LagDistance);

	UKismetSystemLibrary::DrawDebugLine(TraceParams.World, P0, P2
										, FLinearColor::Red, 1, 1);

	// 중간 선만 기준으로 우선 설정한다.
	for (int i = 1; i < InterpCount; i++)
	{
		const float Percent = InterpCount == 0
								? 1
								: i / static_cast<float>(InterpCount);

		const FVector BezierPoint = FMathUtil::GetBezierPoint(
			P0, P1, P2, Percent);

		TraceParams.SquareInfo.Position = BezierPoint;

		TraceParams.SquareInfo.ForwardVector = FMath::Lerp(
			BossHandCacheData[HandType].GetPrevHandForwardVector()
			, CurrentBossHandBox[HandType]->GetForwardVector(), Percent);

		TraceParams.SquareInfo.UpVector = FMath::Lerp(
			BossHandCacheData[HandType].GetPrevHandUpVector()
			, CurrentBossHandBox[HandType]->GetUpVector(), Percent);

		FTraceUtil::SquareTraceMulti(TraceParams, IgnoreActors, HitResults);
		OnTraceAttackHit_Internal();
	}

	FBoxTraceParams BoxTraceParams;
	BoxTraceParams.World = TraceParams.World;
	BoxTraceParams.IsShowDebugTrace = TraceParams.IsShowDebugTrace;
	BoxTraceParams.BoxExtents = CurrentBossHandBox[HandType]->
		GetScaledBoxExtent();

	BoxTraceParams.StartSquareInfo.Position = BossHandCacheData[HandType].
		GetPrevHandPosition();
	BoxTraceParams.StartSquareInfo.ForwardVector = BossHandCacheData[HandType].
		GetPrevHandForwardVector();
	BoxTraceParams.StartSquareInfo.UpVector = BossHandCacheData[HandType].
		GetPrevHandUpVector();

	BoxTraceParams.EndSquareInfo.Position = CurrentBossHandBox[HandType]->
		GetComponentLocation();
	BoxTraceParams.EndSquareInfo.ForwardVector = CurrentBossHandBox[HandType]->
		GetForwardVector();
	BoxTraceParams.EndSquareInfo.UpVector = CurrentBossHandBox[HandType]->
		GetUpVector();

	FTraceUtil::BoxTraceMulti(BoxTraceParams, IgnoreActors, HitResults);
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

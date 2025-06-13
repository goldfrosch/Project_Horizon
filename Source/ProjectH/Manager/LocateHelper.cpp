#include "LocateHelper.h"
#include "ProjectH/GlobalEnum.h"

EDirection2D FLocateHelper::GetDirectionByAngle(const float Angle)
{
	if (Angle > -22.5f && Angle <= 22.5f)
	{
		return EDirection2D::F;
	}
	if (Angle > 22.5f && Angle <= 67.5f)
	{
		return EDirection2D::FL;
	}
	if (Angle > 67.5f && Angle <= 112.5f)
	{
		return EDirection2D::L;
	}
	if (Angle > 112.5f && Angle <= 157.5f)
	{
		return EDirection2D::BL;
	}
	if (Angle > 157.5f || Angle <= -157.5f)
	{
		return EDirection2D::B;
	}
	if (Angle > -157.5f && Angle <= -112.5f)
	{
		return EDirection2D::BR;
	}
	if (Angle > -112.5f && Angle <= -67.5f)
	{
		return EDirection2D::R;
	}
	if (Angle > -67.5f && Angle <= -22.5f)
	{
		return EDirection2D::FR;
	}
	return EDirection2D::B;
}

float FLocateHelper::GetDeltaAngle(const FVector& From, const FVector& To)
{
	const FVector NormalizedFrom = From.GetSafeNormal();
	const FVector NormalizedTo = To.GetSafeNormal();

	// 내적(Dot Product) 이용해서 두 벡터의 각도 계산
	const float Dot = FVector::DotProduct(NormalizedFrom, NormalizedTo);
	float Angle = FMath::RadiansToDegrees(FMath::Acos(Dot));

	// 외적(Cross Product) 사용해서 왼쪽/오른쪽 판별
	const FVector Cross = FVector::CrossProduct(NormalizedFrom, NormalizedTo);
	if (Cross.Z < 0) // Z값이 음수면 왼쪽 방향 (반시계)
	{
		Angle *= -1;
	}

	return Angle; // -180 ~ 180 범위의 각도 반환
}

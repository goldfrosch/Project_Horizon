#pragma once

enum class EDirection2D : uint8;

class FLocateUtil
{
public:
	static EDirection2D GetDirectionByAngle(const float Angle);

	static float GetDeltaAngle(const FVector& From, const FVector& To);
};

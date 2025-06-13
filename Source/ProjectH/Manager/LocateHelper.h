#pragma once

enum class EDirection2D : uint8;

class FLocateHelper
{
public:
	static EDirection2D GetDirectionByAngle(const float Angle);

	static float GetDeltaAngle(const FVector& From, const FVector& To);
};

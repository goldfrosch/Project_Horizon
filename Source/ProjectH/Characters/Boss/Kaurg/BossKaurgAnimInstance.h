#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BossKaurgAnimInstance.generated.h"

UCLASS()
class PROJECTH_API UBossKaurgAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	uint8 IsInAir : 1 = false;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FVector Velocity;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FVector MoveToVelocity;
};

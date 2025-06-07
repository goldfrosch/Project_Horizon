#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ProjectH/Utils/MacroUtil.h"
#include "BaseCharacterAnimInstance.generated.h"

class APlayerCharacter;
class UCharacterMovementComponent;

UCLASS()
class PROJECTH_API UBaseCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GroundSpeed_H;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GroundSpeed_V;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShouldMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsFalling;
	
protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY()
	TObjectPtr<APlayerCharacter> Player;

	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> MovementComponent;
};

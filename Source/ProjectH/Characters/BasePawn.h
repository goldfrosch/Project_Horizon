#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "ProjectH/Utils/MacroUtil.h"

#include "BasePawn.generated.h"

class UPawnMotionWarpingComponent;
class URotatingMovementComponent;
class UHorizonAbilitySystemInitializeData;
class UHorizonAbilitySystemComponent;
class UATR_BaseAttribute;
class UFloatingPawnMovement;

struct FOnAttributeChangeData;

UCLASS()
class PROJECTH_API ABasePawn : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABasePawn();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	GETTER_EDITABLE(TObjectPtr<USkeletalMeshComponent>, Mesh)
	GETTER_EDITABLE(TObjectPtr<UFloatingPawnMovement>, FloatingPawnMovement)
	GETTER_EDITABLE(TObjectPtr<UPawnMotionWarpingComponent>
					, PawnMotionWarpingComponent)
	GETTER(bool, IsInAir)

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Options|GAS")
	TObjectPtr<UHorizonAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UATR_BaseAttribute> Attribute;

	virtual void InitializeAbilitySystem();

	virtual void Tick(float DeltaSeconds) override;

	void OnHealthChanged(const FOnAttributeChangeData& Data);

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> Mesh;

#pragma region Movement
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> FootPos;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<UPawnMotionWarpingComponent> PawnMotionWarpingComponent;

	FVector GravityVelocity = {0, 0, 0};

	UPROPERTY(EditDefaultsOnly, Category = "Options|Movement"
		, meta = (AllowPrivateAccess = true))
	float Gravity = 980.f;

	UPROPERTY(VisibleInstanceOnly, Category = "Options|Movement"
		, meta = (AllowPrivateAccess = true))
	uint8 IsInAir : 1 = false;

	void PerformGravity_Internal(const float DeltaSeconds);

	void PerformRootMotionAnimation_Internal();
#pragma endregion
};

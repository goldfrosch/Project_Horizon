#pragma once

#include "CoreMinimal.h"
#include "ProjectH/Characters/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class UPlayerCameraManageComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputBindingNotified
											, UEnhancedInputComponent*
											, EnhancedInputComponent);

struct FInputActionValue;

class UInputAction;
class UInputComponent;
class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;

UCLASS()
class PROJECTH_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	FOnInputBindingNotified OnInputBindingNotified;

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(
		UInputComponent* PlayerInputComponent) override;
	
	virtual void OnRep_PlayerState() override;
	
	virtual void PossessedBy(AController* NewController) override;

private:
#pragma region Camera Actor Components
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UPlayerCameraManageComponent> PlayerCameraManageComponent;

	void InitializeCamera_Internal();
#pragma endregion

#pragma region Skeletal Actor Components
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> Custom_Hair;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> Custom_Beard;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> Custom_HandLeft;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> Custom_HandRight;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> Custom_LowerBody;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> Custom_UpperBody;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> Custom_Foot;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> Custom_Hood;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> Custom_Shoulder;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> Custom_ShoulderBack;
	
	void InitializeCustomMesh_Internal();
#pragma endregion
	
	UPROPERTY(EditDefaultsOnly, Category = "Options|Input"
		, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Options|Input"
		, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> MoveInputAction;

	UFUNCTION()
	void MoveTo(const FInputActionValue& Value);
};

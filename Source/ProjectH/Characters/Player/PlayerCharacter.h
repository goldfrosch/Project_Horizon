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
#pragma region Actor Components
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UPlayerCameraManageComponent> PlayerCameraManageComponent;

	void InitializeCamera_Internal();
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

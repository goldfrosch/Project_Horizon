#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerCameraManageComponent.generated.h"

class UInputAction;
struct FInputActionValue;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTH_API UPlayerCameraManageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerCameraManageComponent();

protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType
								, FActorComponentTickFunction*
								ThisTickFunction) override;

	virtual void InitializeComponent() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Options|Input"
		, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> LookInputAction;

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void AddInputData_Internal(UEnhancedInputComponent* EnhancedInputComponent);
};

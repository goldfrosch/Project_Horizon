#pragma once

#include "CoreMinimal.h"
#include "ProjectH/Characters/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputBindingNotified
											, UEnhancedInputComponent*
											, EnhancedInputComponent);

class UInputAction;
class UInputComponent;
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
};

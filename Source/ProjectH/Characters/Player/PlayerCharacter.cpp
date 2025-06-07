#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

APlayerCharacter::APlayerCharacter()
{
	InitializeCamera_Internal();
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (const APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
				PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void APlayerCharacter::SetupPlayerInputComponent(
	UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<
		UEnhancedInputComponent>(PlayerInputComponent);
	
	if (!EnhancedInputComponent)
	{
		return;
	}
	
	EnhancedInputComponent->BindAction(MoveInputAction
									   , ETriggerEvent::Triggered, this
									   , &ThisClass::MoveTo);
	EnhancedInputComponent->BindAction(LookInputAction
									   , ETriggerEvent::Triggered, this
									   , &ThisClass::Look);
	
	OnInputBindingNotified.Broadcast(EnhancedInputComponent);
}

void APlayerCharacter::MoveTo(const FInputActionValue& Value)
{
	const FVector2d MovementVector = Value.Get<FVector2d>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).
			GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(
			EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.X);
		AddMovementInput(RightDirection, MovementVector.Y);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	const FVector2d LookToValue = Value.Get<FVector2d>();
	
	AddControllerYawInput(LookToValue.X);
	AddControllerPitchInput(LookToValue.Y);
}

void APlayerCharacter::InitializeCamera_Internal()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(GetMesh());
	
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetRelativeLocation({0, 0, 160});
	SpringArm->SetRelativeRotation({0, 0, 0});
	SpringArm->TargetArmLength = 240.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArm);

	CameraComponent->SetRelativeLocation({0, 0, 0});
	CameraComponent->SetRelativeRotation({0, 0, -18});
}

#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/PlayerCameraManageComponent.h"
#include "GameFramework/SpringArmComponent.h"

APlayerCharacter::APlayerCharacter()
{
	InitializeCamera_Internal();
	InitializeCustomMesh_Internal();
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
	
	PlayerCameraManageComponent = CreateDefaultSubobject<UPlayerCameraManageComponent>("Player Camera Manage Component");
}

void APlayerCharacter::InitializeCustomMesh_Internal()
{
	Custom_Hair = CreateDefaultSubobject<USkeletalMeshComponent>("Custom Hair");
	Custom_Hair->SetupAttachment(GetMesh(), "HAIR");
	Custom_Hair->SetLeaderPoseComponent(GetMesh());
	
	Custom_Beard = CreateDefaultSubobject<USkeletalMeshComponent>("Custom Beard");
	Custom_Beard->SetupAttachment(GetMesh());
	Custom_Beard->SetLeaderPoseComponent(GetMesh());
	
	Custom_HandLeft = CreateDefaultSubobject<USkeletalMeshComponent>("Custom Hand Left");
	Custom_HandLeft->SetupAttachment(GetMesh());
	Custom_HandLeft->SetLeaderPoseComponent(GetMesh());
	
	Custom_HandRight = CreateDefaultSubobject<USkeletalMeshComponent>("Custom Hand Right");
	Custom_HandRight->SetupAttachment(GetMesh());
	Custom_HandRight->SetLeaderPoseComponent(GetMesh());
	
	Custom_LowerBody = CreateDefaultSubobject<USkeletalMeshComponent>("Custom Lower Body");
	Custom_LowerBody->SetupAttachment(GetMesh());
	Custom_LowerBody->SetLeaderPoseComponent(GetMesh());
	
	Custom_UpperBody = CreateDefaultSubobject<USkeletalMeshComponent>("Custom Upper Body");
	Custom_UpperBody->SetupAttachment(GetMesh());
	Custom_UpperBody->SetLeaderPoseComponent(GetMesh());
	
	Custom_Foot = CreateDefaultSubobject<USkeletalMeshComponent>("Custom Foot");
	Custom_Foot->SetupAttachment(GetMesh());
	Custom_Foot->SetLeaderPoseComponent(GetMesh());
	
	Custom_Hood = CreateDefaultSubobject<USkeletalMeshComponent>("Custom Hood");
	Custom_Hood->SetupAttachment(GetMesh());
	Custom_Hood->SetLeaderPoseComponent(GetMesh());
	
	Custom_Shoulder = CreateDefaultSubobject<USkeletalMeshComponent>("Custom Shoulder");
	Custom_Shoulder->SetupAttachment(GetMesh());
	Custom_Shoulder->SetLeaderPoseComponent(GetMesh());
	
	Custom_ShoulderBack = CreateDefaultSubobject<USkeletalMeshComponent>("Custom Shoulder Back");
	Custom_ShoulderBack->SetupAttachment(GetMesh());
	Custom_ShoulderBack->SetLeaderPoseComponent(GetMesh());
}

#include "PlayerCameraManageComponent.h"
#include "EnhancedInputComponent.h"

#include "ProjectH/Characters/Player/PlayerCharacter.h"

UPlayerCameraManageComponent::UPlayerCameraManageComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	bWantsInitializeComponent = true;
}

void UPlayerCameraManageComponent::InitializeComponent()
{
	Super::InitializeComponent();

	APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwner());

	Player->OnInputBindingNotified.AddUniqueDynamic(
		this, &ThisClass::AddInputData_Internal);
}

void UPlayerCameraManageComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UPlayerCameraManageComponent::TickComponent(
	float DeltaTime, ELevelTick TickType
	, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UPlayerCameraManageComponent::Look(const FInputActionValue& Value)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwner());
	const FVector2d LookToValue = Value.Get<FVector2d>();
	
	Player->AddControllerYawInput(LookToValue.X);
	Player->AddControllerPitchInput(LookToValue.Y);
}

void UPlayerCameraManageComponent::AddInputData_Internal(UEnhancedInputComponent* EnhancedInputComponent)
{
	
	EnhancedInputComponent->BindAction(LookInputAction
									   , ETriggerEvent::Triggered, this
									   , &ThisClass::Look);
}


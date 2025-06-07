#include "PlayerCameraManageComponent.h"

UPlayerCameraManageComponent::UPlayerCameraManageComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
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


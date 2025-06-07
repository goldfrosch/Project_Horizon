#include "CustomBodyComponent.h"


UCustomBodyComponent::UCustomBodyComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCustomBodyComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCustomBodyComponent::TickComponent(float DeltaTime, ELevelTick TickType
										, FActorComponentTickFunction*
										ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


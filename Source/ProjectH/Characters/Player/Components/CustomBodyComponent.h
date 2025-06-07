#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomBodyComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTH_API UCustomBodyComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCustomBodyComponent();

protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType
								, FActorComponentTickFunction*
								ThisTickFunction) override;
};

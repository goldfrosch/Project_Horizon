#include "BasePawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ProjectH/GAS/_Common/HorizonAbilitySystemComponent.h"
#include "ProjectH/GAS/_Common/Attribute/ATR_BaseAttribute.h"
#include "ProjectH/GAS/_Common/Tag/HorizonGameplayTag.h"


ABasePawn::ABasePawn()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(
		"Floating Movement Component");

	PrimaryActorTick.bCanEverTick = true;
}

UAbilitySystemComponent* ABasePawn::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABasePawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	PerformGravity_Internal(DeltaSeconds);
}

void ABasePawn::InitializeAbilitySystem()
{
	AbilitySystemComponent->Initialize();
	AbilitySystemComponent->
		GetGameplayAttributeValueChangeDelegate(Attribute->GetHealthAttribute())
		.AddUObject(this, &ThisClass::OnHealthChanged);
}

void ABasePawn::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	const float NewHealth = Data.NewValue;

	Attribute->SetHealth(NewHealth > 0 ? NewHealth : 0);

	if (Attribute->GetHealth() == 0)
	{
		FGameplayTagContainer TagContainer;
		TagContainer.AddTag(HorizonGameplayTags::Default_Passive_Died);

		AbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);
	}
}

void ABasePawn::PerformGravity_Internal(const float DeltaSeconds)
{
	// 기본적으로 중력 값이 커질 수록 내려간다.
	GravityVelocity.Z += Gravity * -1 * DeltaSeconds;

	FHitResult HitResult;

	const FVector DeltaMoveTo = GravityVelocity * 2;

	const float HalfHeight = Mesh->Bounds.BoxExtent.Z;
	const FVector SkeletalMeshBottom = GetActorLocation() - Mesh->GetUpVector()
		* HalfHeight;

	const FVector LineTraceStartLocation = GetActorLocation();
	const FVector LineTraceEndLocation = SkeletalMeshBottom + DeltaMoveTo;

	UKismetSystemLibrary::LineTraceSingle(GetWorld(), LineTraceStartLocation
										, LineTraceEndLocation, TraceTypeQuery1
										, true, TArray<AActor*>()
										, EDrawDebugTrace::ForOneFrame
										, HitResult, true);

	// 겹친 블럭이 있는 경우는 공중에 있지 않다고 처리한다.
	IsInAir = !HitResult.IsValidBlockingHit();

	if (!IsInAir)
	{
		GravityVelocity.Z = 0.f;
	}
}

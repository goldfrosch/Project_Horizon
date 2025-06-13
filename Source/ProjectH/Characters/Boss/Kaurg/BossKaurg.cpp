#include "BossKaurg.h"

#include "Components/BossKaurgCombatComponent.h"
#include "Components/BoxComponent.h"
#include "ProjectH/GAS/_Common/HorizonAbilitySystemComponent.h"
#include "ProjectH/GAS/_Common/Attribute/ATR_BaseAttribute.h"


ABossKaurg::ABossKaurg()
{
	AbilitySystemComponent = CreateDefaultSubobject<
		UHorizonAbilitySystemComponent>("Ability System Component");

	Attribute = CreateDefaultSubobject<UATR_BaseAttribute>(TEXT("Attribute"));

	CollisionBox = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	CollisionBox->SetBoxExtent({136, 240, 180});
	CollisionBox->SetupAttachment(GetRootComponent());

	GetMesh()->SetRelativeLocation({0, -28, -180});
	GetMesh()->SetupAttachment(CollisionBox);

	BossKaurgCombatComponent = CreateDefaultSubobject<
		UBossKaurgCombatComponent>("Boss Kaurg Combat Component");

	BossKaurgCombatComponent->SetRightHandAttackRegion(
		CreateDefaultSubobject<UBoxComponent>("Right Hand Attack Region"));
	BossKaurgCombatComponent->GetRightHandAttackRegion()->SetupAttachment(
		GetMesh(), "AttackHand_R");
	BossKaurgCombatComponent->GetRightHandAttackRegion()->SetRelativeLocation({
		10, 0, 0
	});
	BossKaurgCombatComponent->GetRightHandAttackRegion()->SetBoxExtent({
		56, 40, 16
	});

	BossKaurgCombatComponent->SetLeftHandAttackRegion(
		CreateDefaultSubobject<UBoxComponent>("Left Hand Attack Region"));
	BossKaurgCombatComponent->GetLeftHandAttackRegion()->SetupAttachment(
		GetMesh(), "AttackHand_L");
	BossKaurgCombatComponent->GetLeftHandAttackRegion()->SetRelativeLocation({
		10, 0, 0
	});
	BossKaurgCombatComponent->GetLeftHandAttackRegion()->SetBoxExtent({
		56, 40, 16
	});
}

void ABossKaurg::BeginPlay()
{
	Super::BeginPlay();

	InitializeAbilitySystem();
}

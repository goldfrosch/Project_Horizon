#include "KaurgComboAttackNotifyState.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ProjectH/Characters/Boss/Kaurg/BossKaurg.h"
#include "ProjectH/Characters/Boss/Kaurg/Components/BossKaurgCombatComponent.h"
#include "ProjectH/Utils/MathUtil.h"

void UKaurgComboAttackNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp
												, UAnimSequenceBase* Animation
												, float TotalDuration
												, const
												FAnimNotifyEventReference&
												EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	const ABossKaurg* OwnerBoss = Cast<ABossKaurg>(MeshComp->GetOwner());

	if (!OwnerBoss)
	{
		return;
	}

	UBossKaurgCombatComponent* BossKaurgCombatComponent = OwnerBoss->
		GetBossKaurgCombatComponent();

	if (IsLeftEnabled)
	{
		const FVector InitialLeftLocation = BossKaurgCombatComponent->
											GetLeftHandAttackRegion()->
											GetComponentLocation();

		BossKaurgCombatComponent->SetPrevLeftHandPosition(InitialLeftLocation);
	}

	if (IsRightEnabled)
	{
		const FVector InitialRightLocation = BossKaurgCombatComponent->
											GetRightHandAttackRegion()->
											GetComponentLocation();

		BossKaurgCombatComponent->SetPrevLeftHandPosition(InitialRightLocation);
	}
}

void UKaurgComboAttackNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp
											, UAnimSequenceBase* Animation
											, float FrameDeltaTime
											, const FAnimNotifyEventReference&
											EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	const ABossKaurg* OwnerBoss = Cast<ABossKaurg>(MeshComp->GetOwner());

	if (!OwnerBoss)
	{
		return;
	}

	UBossKaurgCombatComponent* BossKaurgCombatComponent = OwnerBoss->
		GetBossKaurgCombatComponent();

	if (IsLeftEnabled)
	{
		const FVector PrevLeftLocation = BossKaurgCombatComponent->
			GetPrevLeftHandPosition();
		const FVector NextLeftLocation = BossKaurgCombatComponent->
										GetLeftHandAttackRegion()->
										GetComponentLocation();

		const FVector BezierMidPoint =
			FMathUtil::GetBezierControlPointByVectors(
				PrevLeftLocation, NextLeftLocation, 5);

		UKismetSystemLibrary::DrawDebugSphere(MeshComp->GetOwner()->GetWorld()
											, FMathUtil::GetBezierPoint(
												PrevLeftLocation, BezierMidPoint
												, NextLeftLocation, 0.5), 100
											, 12, FLinearColor::Red, 2, 1);

		BossKaurgCombatComponent->SetPrevLeftHandPosition(NextLeftLocation);
	}

	if (IsRightEnabled)
	{
		const FVector NextRightLocation = BossKaurgCombatComponent->
										GetRightHandAttackRegion()->
										GetComponentLocation();

		BossKaurgCombatComponent->SetPrevLeftHandPosition(NextRightLocation);
	}
}

void UKaurgComboAttackNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp
											, UAnimSequenceBase* Animation
											, const FAnimNotifyEventReference&
											EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}

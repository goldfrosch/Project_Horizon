#include "KaurgComboAttackNotifyState.h"

#include "Components/BoxComponent.h"
#include "ProjectH/Characters/Boss/Kaurg/BossKaurg.h"
#include "ProjectH/Characters/Boss/Kaurg/Components/BossKaurgCombatComponent.h"

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
		BossKaurgCombatComponent->CaptureLeftHandPosition();
	}

	if (IsRightEnabled)
	{
		BossKaurgCombatComponent->CaptureRightHandPosition();
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

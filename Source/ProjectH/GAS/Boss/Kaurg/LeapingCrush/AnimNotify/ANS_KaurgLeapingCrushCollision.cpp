#include "ANS_KaurgLeapingCrushCollision.h"

#include "Components/BoxComponent.h"
#include "ProjectH/Characters/Boss/Kaurg/BossKaurg.h"

void UANS_KaurgLeapingCrushCollision::NotifyBegin(
	USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation
	, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	ABossKaurg* BossKaurg = Cast<ABossKaurg>(MeshComp->GetOwner());
	if (!BossKaurg->IsValidLowLevel())
	{
		return;
	}

	BossKaurg->GetCollisionBox()->SetCollisionResponseToChannel(
		ECC_Pawn, ECR_Ignore);
}

void UANS_KaurgLeapingCrushCollision::NotifyEnd(USkeletalMeshComponent* MeshComp
												, UAnimSequenceBase* Animation
												, const
												FAnimNotifyEventReference&
												EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	ABossKaurg* BossKaurg = Cast<ABossKaurg>(MeshComp->GetOwner());
	if (!BossKaurg->IsValidLowLevel())
	{
		return;
	}

	BossKaurg->GetCollisionBox()->SetCollisionResponseToChannel(
		ECC_Pawn, ECR_Block);
}

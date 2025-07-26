#include "ANS_PawnMotionWarping.h"

#include "PawnMotionWarpingComponent.h"

void UANS_PawnMotionWarping::NotifyBegin(USkeletalMeshComponent* MeshComp
										, UAnimSequenceBase* Animation
										, float TotalDuration
										, const FAnimNotifyEventReference&
										EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (UPawnMotionWarpingComponent* PawnMotionWarpingComponent = MeshComp->
		GetOwner()->FindComponentByClass<UPawnMotionWarpingComponent>())
	{
		PawnMotionWarpingComponent->
			SelectMotionWarping(WarpName, TotalDuration);
	}
}

void UANS_PawnMotionWarping::NotifyTick(USkeletalMeshComponent* MeshComp
										, UAnimSequenceBase* Animation
										, float FrameDeltaTime
										, const FAnimNotifyEventReference&
										EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (UPawnMotionWarpingComponent* PawnMotionWarpingComponent = MeshComp->
		GetOwner()->FindComponentByClass<UPawnMotionWarpingComponent>())
	{
		PawnMotionWarpingComponent->UpdateBlendMotion(FrameDeltaTime);
	}
}

void UANS_PawnMotionWarping::NotifyEnd(USkeletalMeshComponent* MeshComp
										, UAnimSequenceBase* Animation
										, const FAnimNotifyEventReference&
										EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (UPawnMotionWarpingComponent* PawnMotionWarpingComponent = MeshComp->
		GetOwner()->FindComponentByClass<UPawnMotionWarpingComponent>())
	{
		PawnMotionWarpingComponent->SelectMotionWarping(NAME_None);
	}
}

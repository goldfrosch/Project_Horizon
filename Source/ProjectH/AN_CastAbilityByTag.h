#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_CastAbilityByTag.generated.h"

UCLASS()
class PROJECTH_API UAN_CastAbilityByTag : public UAnimNotify
{
	GENERATED_BODY()

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp
						, UAnimSequenceBase* Animation
						, const FAnimNotifyEventReference&
						EventReference) override;

private:
	UPROPERTY(EditInstanceOnly, meta = (AllowPrivateAccess = true))
	FGameplayTag SkillTag;
};

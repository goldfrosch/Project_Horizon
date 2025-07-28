#include "AN_CastAbilityByTag.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"


void UAN_CastAbilityByTag::Notify(USkeletalMeshComponent* MeshComp
								, UAnimSequenceBase* Animation
								, const FAnimNotifyEventReference&
								EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	UAbilitySystemComponent* AbilitySystemComponent =
		UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(
			MeshComp->GetOwner());

	if (!AbilitySystemComponent->IsValidLowLevel())
	{
		return;
	}

	FGameplayTagContainer GameplayTagContainer;
	GameplayTagContainer.AddTag(SkillTag);

	AbilitySystemComponent->TryActivateAbilitiesByTag(GameplayTagContainer);
}

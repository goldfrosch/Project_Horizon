#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_ActiveGameplayAbility.generated.h"

class UGA_BaseAbility;
class UGameplayAbility;

UCLASS()
class PROJECTH_API UBTT_ActiveGameplayAbility : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTT_ActiveGameplayAbility();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp
											, uint8* NodeMemory) override;

	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp
										, uint8* NodeMemory) override;

private:
	UPROPERTY(EditInstanceOnly, Category = "Options"
		, meta = (AllowPrivateAccess = true))
	FGameplayTag TargetSkillTag;

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> CurrentOwnerComp = nullptr;

	UPROPERTY()
	TObjectPtr<UGameplayAbility> CurrentAbilityInstance;

	UFUNCTION()
	void OnAbilityEnd_Internal(UGameplayAbility* Data);
	UFUNCTION()
	void OnAbilityCancel_Internal();
};

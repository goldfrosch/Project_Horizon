#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_HasGameplayTag.generated.h"

UCLASS()
class PROJECTH_API UBTD_HasGameplayTag : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTD_HasGameplayTag();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp
											, uint8* NodeMemory) const override;

private:
	UPROPERTY(EditInstanceOnly, Category = "Options"
		, meta = (AllowPrivateAccess = true))
	FGameplayTag Tag;
};

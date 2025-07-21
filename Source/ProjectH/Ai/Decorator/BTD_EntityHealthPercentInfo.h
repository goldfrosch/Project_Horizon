#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_EntityHealthPercentInfo.generated.h"

UENUM()
enum class EBTD_EntityHealthPercentCalcType : uint8
{
	Greater, Less, Equal
};

UCLASS()
class PROJECTH_API UBTD_EntityHealthPercentInfo : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTD_EntityHealthPercentInfo();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp
											, uint8* NodeMemory) const override;

private:
	UPROPERTY(EditInstanceOnly, meta = (AllowPrivateAccess = true))
	EBTD_EntityHealthPercentCalcType HealthPercentCalcType =
		EBTD_EntityHealthPercentCalcType::Equal;

	UPROPERTY(EditInstanceOnly
		, meta = (AllowPrivateAccess = true, ClampMin = 0, ClampMax = 100))
	float Percent;
};

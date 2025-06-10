#pragma once

#include "CoreMinimal.h"
#include "ProjectH/GAS/_Common/Attribute/ATR_BaseAttribute.h"
#include "ATR_PlayerAttribute.generated.h"

UCLASS()
class PROJECTH_API UATR_PlayerAttribute : public UATR_BaseAttribute
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category="Attributes"
		, ReplicatedUsing = OnRepMana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UATR_PlayerAttribute, Mana)

	UPROPERTY(BlueprintReadOnly, Category="Attributes"
		, ReplicatedUsing = OnRepMaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UATR_PlayerAttribute, MaxMana)
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes"
		, ReplicatedUsing = OnRepStamina)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UATR_PlayerAttribute, Stamina)

	UPROPERTY(BlueprintReadOnly, Category="Attributes"
		, ReplicatedUsing = OnRepMaxStamina)
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UATR_PlayerAttribute, MaxStamina)
	
protected:
	virtual void GetLifetimeReplicatedProps(
		TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	UFUNCTION()
	virtual void OnRepMana(const FGameplayAttributeData& OldMana);
	
	UFUNCTION()
	virtual void OnRepMaxMana(const FGameplayAttributeData& OldMaxMana);
	
	UFUNCTION()
	virtual void OnRepStamina(const FGameplayAttributeData& OldStamina);
	
	UFUNCTION()
	virtual void OnRepMaxStamina(const FGameplayAttributeData& OldMaxStamina);
};

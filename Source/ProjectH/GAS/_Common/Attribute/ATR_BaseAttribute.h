#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ATR_BaseAttribute.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class PROJECTH_API UATR_BaseAttribute : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category="Attributes"
		, ReplicatedUsing = OnRepHealth)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UATR_BaseAttribute, Health)

	UPROPERTY(BlueprintReadOnly, Category="Attributes"
		, ReplicatedUsing = OnRepMaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UATR_BaseAttribute, MaxHealth)
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes"
		, ReplicatedUsing = OnRepMovementSpeed)
	FGameplayAttributeData MovementSpeed;
	ATTRIBUTE_ACCESSORS(UATR_BaseAttribute, MovementSpeed)

protected:
	virtual void GetLifetimeReplicatedProps(
		TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	UFUNCTION()
	virtual void OnRepHealth(const FGameplayAttributeData& OldHealth);
	
	UFUNCTION()
	virtual void OnRepMaxHealth(const FGameplayAttributeData& OldMaxHealth);
	
	UFUNCTION()
	virtual void OnRepMovementSpeed(const FGameplayAttributeData& OldMovementSpeed);
};

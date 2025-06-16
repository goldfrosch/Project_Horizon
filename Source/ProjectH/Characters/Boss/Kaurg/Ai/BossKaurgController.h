// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "BossKaurgController.generated.h"

UCLASS()
class PROJECTH_API ABossKaurgController : public AAIController
{
	GENERATED_BODY()

public:
	ABossKaurgController();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Options"
		, meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTree> BehaviorTree;
};

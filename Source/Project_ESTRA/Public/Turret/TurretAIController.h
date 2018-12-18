// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "TurretAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ESTRA_API ATurretAIController : public AAIController
{
	GENERATED_BODY()

public:

	ATurretAIController(const FObjectInitializer & ObjectInitializer);

	void BeginPlay() override;

private:

	// Òhese are the behavior tree and the according blackboard that controls our controller (the AI happens in them)
	UPROPERTY(EditDefaultsOnly, Category = "Blackboard")
	UBlackboardData * BlackboardToUse;
	UPROPERTY(EditDefaultsOnly, Category = "Blackboard")
	UBehaviorTree* BehaviorTreeToUse;

	UPROPERTY()
	UBlackboardComponent* BB;

};

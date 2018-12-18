// Fill out your copyright notice in the Description page of Project Settings.

#include "TurretAIController.h"

ATurretAIController::ATurretAIController(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void ATurretAIController::BeginPlay()
{
	Super::BeginPlay();

	if (!ensure(BlackboardToUse)) return;
	UseBlackboard(BlackboardToUse, BB);
	
	if (!ensure(BB)) return;
	BB->SetValueAsBool(FName(TEXT("IsAnimationInProgress")), false);
	BB->SetValueAsBool(FName(TEXT("IsHidden")), true);
	BB->SetValueAsBool(FName(TEXT("IsActive")), false);

	if (!ensure(BehaviorTreeToUse)) return;
	RunBehaviorTree(BehaviorTreeToUse);
}
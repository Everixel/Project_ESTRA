// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TurretPawn.generated.h"

UCLASS()
class PROJECT_ESTRA_API ATurretPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATurretPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//The attack range of the turret
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turret")
	float AttackRange = 1000.f;

	//This boolean is a flag that controls whether a debug sphere is drawn during gameplay around a turret's range
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turret")
	bool DrawAttackRangeDuringPlay = false;

	//Procedural animation
	// This sets the target tracking speed of the turret (sideways rotation)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
	float FaceTargetSpeed = 50.f;

	// Animation blueprint controls

	//This property is obseverd by the animation blueprint and controls state machine flow
	UPROPERTY(BlueprintReadWrite, Category = "Turret")
	bool CanDoUnhide = false;

	//This property is obseverd by the animation blueprint and controls state machine flow
	UPROPERTY(BlueprintReadWrite, Category = "Turret")
	bool CanDoHide = false;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Misc.h"
#include "TeamCharacter_Interface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UTeamCharacter_Interface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_ESTRA_API ITeamCharacter_Interface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Team Character Interface")
	void TakeDamage(AActor* DamageDealer, float DamageAmount);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Team Character Interface")
	ETeam GetTeam();
};

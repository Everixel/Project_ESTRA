// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc.generated.h"

UENUM(BlueprintType)
enum class ETeam : uint8
{
	NEUTRAL	UMETA(DisplayName = "Neutral"),
	RED		UMETA(DisplayName = "Red"),
	BLUE	UMETA(DisplayName = "Blue")
};

USTRUCT(BlueprintType)
struct FTeamCharacterStatistics
{
	GENERATED_BODY()

	//The maximum health a character can have - it is a cap
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxHealth = 100.f;
	
	//The minimum health of this character (when the character reaches it it is dead)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinHealth = 0.f;
	
	//The current health of this character
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentHealth = MaxHealth;

	//The team of this character
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETeam Team = ETeam::NEUTRAL;
};

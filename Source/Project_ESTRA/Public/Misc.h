// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ETeam : uint8
{
	NEUTRAL	UMETA(DisplayName = "Neutral"),
	RED		UMETA(DisplayName = "Red"),
	BLUE	UMETA(DisplayName = "Blue")
};

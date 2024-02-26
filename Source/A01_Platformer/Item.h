// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS()
class A01_PLATFORMER_API UItem : public UObject
{
	GENERATED_BODY()

public:
	UItem();
	
	auto SetName(FString Name) -> void;
	auto SetDescription(FString Description) -> void;
	
	auto GetName() -> FString;
	auto GetDescription() -> FString;

protected:
	FString ItemName;
	FString ItemDescription;
};

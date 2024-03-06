// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "SpeedBoostItem.generated.h"

/**
 * 
 */
UCLASS()
class A01_PLATFORMER_API USpeedBoostItem : public UItem
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpeedBoostAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpeedBoostDuration;

	FTimerHandle BoostTimer;

	AA01_PlatformerCharacter* AffectedCharacter;

public:
	USpeedBoostItem();

	virtual void UseItem(AA01_PlatformerCharacter* Character) override;

	auto OnSpeedBoostEnd() -> void;
};

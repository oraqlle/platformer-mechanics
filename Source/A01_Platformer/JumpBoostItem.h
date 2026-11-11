// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "JumpBoostItem.generated.h"

/**
 * 
 */
UCLASS()
class A01_PLATFORMER_API UJumpBoostItem : public UItem
{
	GENERATED_BODY()
	
public:

	UJumpBoostItem();

	virtual void UseItem(AA01_PlatformerCharacter* Character) override;

	auto OnJumpBoostEnd() -> void;
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JumpBoostAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JumpBoostDuration;

	FTimerHandle BoostTimer;

	AA01_PlatformerCharacter* AffectedCharacter;	
};

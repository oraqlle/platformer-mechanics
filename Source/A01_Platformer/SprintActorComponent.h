// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "A01_PlatformerCharacter.h"
#include "Components/ActorComponent.h"
#include "SprintActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class A01_PLATFORMER_API USprintActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USprintActorComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpeedIncrease;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	auto ActivateSprint(AA01_PlatformerCharacter* AffectedCharacter) -> void;

	auto DeactivateSprint(AA01_PlatformerCharacter* AffectedCharacter) -> void;
};

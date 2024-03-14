// Fill out your copyright notice in the Description page of Project Settings.


#include "SprintActorComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
USprintActorComponent::USprintActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SprintIncrease = 500.f;
}


// Called when the game starts
void USprintActorComponent::BeginPlay()
{
	Super::BeginPlay();

		
}

auto USprintActorComponent::ActivateSprint(AA01_PlatformerCharacter* AffectedCharacter) -> void
{
	if (AffectedCharacter)
	{
		AffectedCharacter->GetCharacterMovement()->MaxWalkSpeed += SprintIncrease;
	}
}

auto USprintActorComponent::DeactivateSprint(AA01_PlatformerCharacter* AffectedCharacter) -> void
{
	if (AffectedCharacter)
	{
		AffectedCharacter->GetCharacterMovement()->MaxWalkSpeed -= SprintIncrease;
	}
}

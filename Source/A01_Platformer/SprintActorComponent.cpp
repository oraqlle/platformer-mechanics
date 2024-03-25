// Fill out your copyright notice in the Description page of Project Settings.


#include "SprintActorComponent.h"

#include "A01_Platformer.h"
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
		UE_LOG(
			Sprinting,
			Display,
			TEXT("Player is now sprinting at a speed of: %.3f"),
			AffectedCharacter->GetCharacterMovement()->MaxWalkSpeed);
	}
}

auto USprintActorComponent::DeactivateSprint(AA01_PlatformerCharacter* AffectedCharacter) -> void
{
	if (AffectedCharacter)
	{
		AffectedCharacter->GetCharacterMovement()->MaxWalkSpeed -= SprintIncrease;
		UE_LOG(
			Sprinting,
			Display,
			TEXT("Player is now walking at a speed of: %.3f"),
			AffectedCharacter->GetCharacterMovement()->MaxWalkSpeed);
	}
}

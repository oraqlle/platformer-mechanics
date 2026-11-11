// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveablePlatform.h"
#include "A01_Platformer.h"

// Sets default values
AMoveablePlatform::AMoveablePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementSpeed = 100.f;
	ToleranceThreshold = 10.f;
	GoalIndex = 0;
	bReversed = false;
	EMovementType = EMovement_t::EMovementType_Finite;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform Mesh"));
	PlatformMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMoveablePlatform::BeginPlay()
{
	Super::BeginPlay();

	if (EMovementType == EMovement_t::EMovementType_Reversing
	 || EMovementType == EMovement_t::EMovementType_Looping)
	{
		checkf(
			Waypoints.Num() > 3,
			TEXT("Must have at least 4 waypoints for Reversing and Looping AMovementPlatform, Platform: %s only has %d"),
			*GetName(),
			Waypoints.Num());
	}
}

// Called every frame
void AMoveablePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Waypoints.Num() == 0) { return;	}

	switch (EMovementType)
	{
	case EMovement_t::EMovementType_Finite:
		if (GoalIndex >= Waypoints.Num()) { return; }
		break;
	case EMovement_t::EMovementType_Reversing:
		if (GoalIndex >= Waypoints.Num())
		{
			bReversed = true;
			GoalIndex += bReversed ? -1 : 1;
		}
		else if (GoalIndex < 0)
		{
			bReversed = false;
			GoalIndex += bReversed ? -1 : 1;
		}

		break;
	case EMovement_t::EMovementType_Looping:
		if (GoalIndex >= Waypoints.Num()) { GoalIndex = 0; }
		break;
	}
	
	FVector Direction = Waypoints[GoalIndex] - GetActorLocation();
	Direction.Normalize();
	
	Direction *= MovementSpeed * DeltaTime;
	FVector NewLocation = GetActorLocation() + Direction;

	if (FVector::Distance(Waypoints[GoalIndex], NewLocation) <= ToleranceThreshold)
	{
		UE_LOG(
			PlatformMovement,
			Display,
			TEXT("Moving Platform: %s has arrived at location (x: %.3f, y: %.3f, z: %.3f)"),
			*GetName(),
			NewLocation.Component(0),
			NewLocation.Component(1),
			NewLocation.Component(2));

		NewLocation = Waypoints[GoalIndex];
		GoalIndex += bReversed ? -1 : 1;
	}

	SetActorLocation(NewLocation);
}

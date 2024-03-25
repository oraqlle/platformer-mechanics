// Fill out your copyright notice in the Description page of Project Settings.


#include "HorizontalPlatform.h"
#include "A01_Platformer.h"

// Sets default values
AHorizontalPlatform::AHorizontalPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementDistance = 1000.f;
	MovementSpeed = 100.f;
	ToleranceThreshold = 10.f;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform Mesh"));
	PlatformMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHorizontalPlatform::BeginPlay()
{
	Super::BeginPlay();

	PreviousStartLocation = GetActorLocation();
	CurrentGoal = PreviousStartLocation + FVector(MovementDistance, 0.f, 0.f);
}

// Called every frame
void AHorizontalPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Direction = CurrentGoal - GetActorLocation();
	Direction.Normalize();

	Direction *= MovementSpeed * DeltaTime;
	FVector NewLocation = GetActorLocation() + Direction;

	if (FVector::Distance(CurrentGoal, NewLocation) <= ToleranceThreshold)
	{
		
		UE_LOG(
			PlatformMovement,
			Display,
			TEXT("Moving Platform: %s has arrived at location (x: %.3f, y: %.3f, z: %.3f)"),
			*GetName(),
			NewLocation.Component(0),
			NewLocation.Component(1),
			NewLocation.Component(2));
		
		NewLocation = CurrentGoal;
		CurrentGoal = PreviousStartLocation;
		PreviousStartLocation = NewLocation;
	}

	SetActorLocation(NewLocation);
}


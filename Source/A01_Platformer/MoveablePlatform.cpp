// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveablePlatform.h"

// Sets default values
AMoveablePlatform::AMoveablePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementSpeed = 100.f;
	ToleranceThreshold = 10.f;
	GoalIndex = 0;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform Mesh"));
	PlatformMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMoveablePlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMoveablePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Waypoints.Num() == 0 || GoalIndex >= Waypoints.Num()) { return; }

	FVector Direction = Waypoints[GoalIndex] - GetActorLocation();
	Direction.Normalize();
	
	Direction *= MovementSpeed * DeltaTime;
	FVector NewLocation = GetActorLocation() + Direction;

	if (FVector::Distance(Waypoints[GoalIndex], NewLocation) <= ToleranceThreshold)
	{
		NewLocation = Waypoints[GoalIndex];
		GoalIndex += 1;
	}

	SetActorLocation(NewLocation);
}

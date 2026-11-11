// Fill out your copyright notice in the Description page of Project Settings.


#include "HalfOrbitingActor.h"

#include "A01_Platformer.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AHalfOrbitingActor::AHalfOrbitingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform Mesh"));
	Mesh->SetupAttachment(RootComponent);

	OrbitSpeed = 100.f;
	OrbitRadius = FVector(200.f, 0.f, 0.f);
	StartingAngle = 0.f;
	OrbitAngle = 0.f;
	OriginActor = nullptr;
	bReversed = false;
}

// Called when the game starts or when spawned
void AHalfOrbitingActor::BeginPlay()
{
	Super::BeginPlay();
	
	OrbitAngle = StartingAngle;
}

// Called every frame
void AHalfOrbitingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!OriginActor) { return; }

	auto const DeltaAngle = OrbitSpeed * DeltaTime;
	OrbitAngle += bReversed ? -DeltaAngle : DeltaAngle;
	
	auto const Bounds = OriginActor->GetRootComponent()->Bounds;
	auto const OrbitOrigin = Bounds.Origin;
	auto const PivotValue = OrbitRadius.RotateAngleAxis(OrbitAngle, FVector(0.f, 0.f, 1.f));
	auto const NewLocation = OrbitOrigin + PivotValue + FVector(100.f, 100.f, 0.f);
    
	auto Direction = OrbitOrigin - NewLocation;
	Direction.Normalize();
	FRotator NewRotation = UKismetMathLibrary::MakeRotFromX(Direction);
	NewRotation.Pitch = 0;
	NewRotation.Roll = 0;

	if (OrbitAngle < 0.f)
	{
		 bReversed = false;
		 OrbitAngle = 0.f;
	} else if (OrbitAngle > 180.f)
	{
		 bReversed = true;
		 OrbitAngle = 180.f;
	}

	UE_LOG(
		  PlatformMovement,
		  Display,
		  TEXT("Half Orbiting Platform: %s has arrived at location (x: %.3f, y: %.3f, z: %.3f)"),
		  *GetName(),
		  NewLocation.Component(0),
		  NewLocation.Component(1),
		  NewLocation.Component(2));
	
	SetActorLocationAndRotation(NewLocation, NewRotation);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "HalfOrbitingActor.h"

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
	
	//OrbitAngle = FMath::ClampAngle(StartingAngle, 0.f, 180.f);
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
	auto const Forward = GetActorForwardVector();
	auto const PivotValue = OrbitRadius.RotateAngleAxis(OrbitAngle, FVector(0.f, 0.f, 1.f));
	auto const NewLocation = OrbitOrigin + PivotValue + FVector(100.f, 100.f, 0.f);
    
	auto const Direction = OrbitOrigin - NewLocation;	
	auto const RotationAngleRad = FMath::Acos(Forward.Dot(Direction) / (Forward.Length() * Direction.Length()));
	auto const RotationAngleDeg = FMath::RadiansToDegrees(RotationAngleRad);
	CurrentRotation += (bReversed ? -RotationAngleDeg : RotationAngleDeg) * DeltaTime;

	if (OrbitAngle < 0.f)
	{
		 bReversed = false;
		 OrbitAngle = 0.f;
	} else if (OrbitAngle > 180.f)
	{
		 bReversed = true;
		 OrbitAngle = 180.f;
	}

	auto const Rotation = FRotator(0.0, CurrentRotation, 0.0);
	
	SetActorLocationAndRotation(NewLocation, Rotation);
}


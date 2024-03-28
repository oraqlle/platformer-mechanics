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
}

// Called when the game starts or when spawned
void AHalfOrbitingActor::BeginPlay()
{
	Super::BeginPlay();
	
	OrbitAngle = FMath::ClampAngle(StartingAngle, 0.f, 180.f);
}

// Called every frame
void AHalfOrbitingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!OriginActor) { return; }

	float const DeltaAngle = OrbitSpeed * DeltaTime;
	OrbitAngle += bReversed ? -DeltaAngle : DeltaAngle;
	
	if (OrbitAngle < 0.f)
	{
		bReversed = false;
		OrbitAngle = 0.f;
	} else if (180.f < OrbitAngle)
	{
		bReversed = true;
		OrbitAngle = 180.f;
	}
	
	auto const Bounds = OriginActor->GetRootComponent()->Bounds;
	auto const Origin = Bounds.Origin;
	FVector const RotateValue = OrbitRadius.RotateAngleAxis(OrbitAngle, FVector(0.f, 0.f, 1.f));
	FVector const NewLocation = Origin + RotateValue;
	
	SetActorLocation(NewLocation);
}


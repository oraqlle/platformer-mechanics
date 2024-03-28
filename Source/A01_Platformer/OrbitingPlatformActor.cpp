// Fill out your copyright notice in the Description page of Project Settings.


#include "OrbitingPlatformActor.h"

// Sets default values
AOrbitingPlatformActor::AOrbitingPlatformActor()
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
void AOrbitingPlatformActor::BeginPlay()
{
	Super::BeginPlay();

	OrbitAngle = StartingAngle;	
}

// Called every frame
void AOrbitingPlatformActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!OriginActor) { return; }

	// OrbitAngle = OrbitSpeed * DeltaTime;
	OrbitAngle += 1.f;

	if (OrbitAngle >= 360.f)
	{
		OrbitAngle -= 360.f;
	}

	auto Bounds = OriginActor->GetRootComponent()->Bounds;
	auto Origin = Bounds.Origin;
	FVector RotateValue = OrbitRadius.RotateAngleAxis(OrbitAngle, FVector(0.f, 0.f, 1.f));
	FVector NewLocation = Origin + RotateValue;
	
	SetActorLocation(NewLocation);

	
}


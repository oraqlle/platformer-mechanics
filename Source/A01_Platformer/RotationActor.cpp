// Fill out your copyright notice in the Description page of Project Settings.


#include "RotationActor.h"

// Sets default values
ARotationActor::ARotationActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform Mesh"));
	PlatformMesh->SetupAttachment(RootComponent);

	RotationSpeed = 180;
	CurrentRotation = 0;
}

// Called when the game starts or when spawned
void ARotationActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARotationActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentRotation += RotationSpeed * DeltaTime;

	if (CurrentRotation >= 360) {
		CurrentRotation -= 360;
    }
    
    FRotator Rotation = FRotator(0,CurrentRotation,0);
    SetActorRotation(Rotation);
}


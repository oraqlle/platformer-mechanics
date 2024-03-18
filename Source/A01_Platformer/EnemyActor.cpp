// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"
#include "A01_PlatformerCharacter.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy Mesh"));
    EnemyMesh->SetupAttachment(RootComponent);
	
    Target = nullptr;
    DamageAmount = 50;
    EnemySpeed = 200;
}

void AEnemyActor::OnEnemyCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, FHitResult const& SweepResult)
{
	if (AA01_PlatformerCharacter* Character = Cast<AA01_PlatformerCharacter>(OtherActor))
	{
		Character->DamagePlayer(DamageAmount);
    }
    Destroy();
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();

	EnemyMesh->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnEnemyCollision);
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Target) { return; }

	FVector Direction = Target->GetActorLocation() - GetActorLocation();
    Direction.Normalize();
    Direction.Z = 0;
    FVector NewLocation = GetActorLocation() + (Direction * EnemySpeed * DeltaTime);

	FRotator EnemyRotation = UKismetMathLibrary::MakeRotFromX(Direction);
    EnemyRotation.Pitch = 0;
    EnemyRotation.Roll = 0;
    SetActorLocationAndRotation(NewLocation, EnemyRotation);
}


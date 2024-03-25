// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnerActor.h"

#include "A01_Platformer.h"
#include "EnemyActor.h"

// Sets default values
AEnemySpawnerActor::AEnemySpawnerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SpawnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spawn Mesh"));
    SpawnerMesh->SetupAttachment(RootComponent);

	SpawningDelay = 5;
    SpawnRadius = 800;
}

void AEnemySpawnerActor::SpawnEnemy()
{
	if (!EnemyTarget) { return; }

	FVector RandomSpawn = FVector(
		GetActorLocation().X + FMath::RandRange(-SpawnRadius, SpawnRadius),
		GetActorLocation().Y + FMath::RandRange(-SpawnRadius, SpawnRadius),
		GetActorLocation().Z);
	
	AEnemyActor* NewEnemy = Cast<AEnemyActor>(GetWorld()->SpawnActor(EnemyClass, &RandomSpawn));
	NewEnemy->Target = EnemyTarget;

	UE_LOG(
		Enemy,
		Display,
		TEXT("Enemy Spawner: %s spawned Enemy: %s at location (x: %.3f, y: %.3f, z: %.3f)"),
		*GetName(),
		*NewEnemy->GetName(),
		RandomSpawn.Component(0),
		RandomSpawn.Component(1),
		RandomSpawn.Component(2));
}

// Called when the game starts or when spawned
void AEnemySpawnerActor::BeginPlay()
{
	Super::BeginPlay();

	EnemyTarget = GetWorld()->GetFirstPlayerController()->GetPawn();
    GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &AEnemySpawnerActor::SpawnEnemy, SpawningDelay, true);
}

// Called every frame
void AEnemySpawnerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


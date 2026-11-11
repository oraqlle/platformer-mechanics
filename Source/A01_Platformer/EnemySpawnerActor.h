// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnerActor.generated.h"

UCLASS()
class A01_PLATFORMER_API AEnemySpawnerActor : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
    TSubclassOf<class AEnemyActor> EnemyClass;

	UPROPERTY(EditAnywhere)
    UStaticMeshComponent* SpawnerMesh;

	UPROPERTY(EditAnywhere)
    float SpawningDelay;

	UPROPERTY(EditAnywhere)
    float SpawnRadius;

	UPROPERTY(EditAnywhere)
    AActor* EnemyTarget;

	FTimerHandle SpawnTimer;
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawnerActor();

	void SpawnEnemy();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

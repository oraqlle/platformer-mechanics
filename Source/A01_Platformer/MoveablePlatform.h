// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoveablePlatform.generated.h"

UCLASS()
class A01_PLATFORMER_API AMoveablePlatform : public AActor
{
	GENERATED_BODY()

	int32 GoalIndex;
	
public:	
	// Sets default values for this actor's properties
	AMoveablePlatform();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* PlatformMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ToleranceThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> Waypoints;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

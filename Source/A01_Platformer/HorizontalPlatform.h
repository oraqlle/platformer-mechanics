// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HorizontalPlatform.generated.h"

UCLASS()
class A01_PLATFORMER_API AHorizontalPlatform : public AActor
{
	GENERATED_BODY()

	FVector CurrentGoal;

	FVector PreviousStartLocation;

public:
	// Sets default values for this actor's properties
	AHorizontalPlatform();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* PlatformMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ToleranceThreshold;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

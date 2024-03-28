// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HalfOrbitingActor.generated.h"

UCLASS()
class A01_PLATFORMER_API AHalfOrbitingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHalfOrbitingActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OrbitSpeed;

	UPROPERTY(EditAnywhere)
	FVector OrbitRadius;
	
	UPROPERTY(EditAnywhere)
	AActor* OriginActor;

	UPROPERTY(EditAnywhere)
	float StartingAngle;

	float OrbitAngle;

	bool bReversed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

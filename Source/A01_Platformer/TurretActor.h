// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurretActor.generated.h"

UCLASS()
class A01_PLATFORMER_API ATurretActor : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditAnywhere)
	float ShootingDelay;

	UPROPERTY(EditAnywhere)
	float FieldOfView;

	UPROPERTY(EditAnywhere)
	float TurretRange;

	UPROPERTY(EditAnywhere)
	AActor* TurretTarget;
	
	bool bCanShoot;

	float ReloadTimer;
	
public:	
	// Sets default values for this actor's properties
	ATurretActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

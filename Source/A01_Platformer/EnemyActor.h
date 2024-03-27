// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActor.generated.h"

UCLASS()
class A01_PLATFORMER_API AEnemyActor : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* EnemyMesh;

	UPROPERTY(EditAnywhere)
	AActor* Target;

	UPROPERTY(EditAnywhere)
	float MovementSpeed;

	UPROPERTY(EditAnywhere)
	float MeleeDamageAmount;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere)
	uint8 MaxAmmo;

	UPROPERTY(EditAnywhere)
	uint8 CurrentAmmo;

	UPROPERTY(EditAnywhere)
	float ShootingRange;

	UPROPERTY(EditAnywhere)
	float ShootingDelay;
	
	bool bCanShoot;

	float FiringDelayTimer;
	
	UPROPERTY(EditAnywhere)
	float ReloadDelay;

	bool bReloading;

	float ReloadTimer;

public:	
	// Sets default values for this actor's properties
	AEnemyActor();

	UFUNCTION()
	void OnEnemyCollision(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
        int32 OtherBodyIndex,
        bool bFromSweep,
        FHitResult const& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

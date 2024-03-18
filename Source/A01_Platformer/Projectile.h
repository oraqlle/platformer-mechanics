// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class A01_PLATFORMER_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere)
	AActor* Parent;

	UPROPERTY(EditAnywhere)
	float MovementSpeed;

	UPROPERTY(EditAnywhere)
	float MaximumLifetime;

	UPROPERTY(EditAnywhere)
	float DamageAmount;
	
	UPROPERTY(EditAnywhere)
	float CurrentLifetime;
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	UFUNCTION()
	void OnProjectileHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
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

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "A01_PlatformerCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "SpikeTrap.generated.h"

UCLASS()
class A01_PLATFORMER_API ASpikeTrap : public AActor
{
	GENERATED_BODY()

	FTimerHandle DamageTimer;

	AA01_PlatformerCharacter* CollidingPlayer;
	
public:	
	// Sets default values for this actor's properties
	ASpikeTrap();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* TrapMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* DamageVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamagePerSecond;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnDamageBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		FHitResult const& SewwpResult);

	UFUNCTION()
	void OnDamageEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	void DamageTime();
};

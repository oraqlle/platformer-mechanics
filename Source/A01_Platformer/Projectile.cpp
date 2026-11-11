// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "A01_PlatformerCharacter.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
    ProjectileMesh->SetupAttachment(RootComponent);

	MovementSpeed = 2500;
    MaximumLifetime = 5;
    CurrentLifetime = 0;
    DamageAmount = 25;
}

void AProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, FHitResult const& SweepResult)
{
	if (!Parent) { return; }
    if (Parent == OtherActor) { return; }

	if (AA01_PlatformerCharacter* Character = Cast<AA01_PlatformerCharacter>(OtherActor); Character)
	{
		Character->DamagePlayer(DamageAmount);
    }
	
    Destroy();
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnProjectileHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentLifetime += DeltaTime;
	
	if (CurrentLifetime >= MaximumLifetime) {
		Destroy();
	}

	FVector Movement = GetActorForwardVector() * (MovementSpeed * DeltaTime);
    FVector NewLocation = GetActorLocation() + Movement;
    SetActorLocation(NewLocation);
}


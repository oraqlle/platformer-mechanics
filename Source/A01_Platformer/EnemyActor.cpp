// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"

#include "A01_Platformer.h"
#include "A01_PlatformerCharacter.h"
#include "Projectile.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy Mesh"));
    EnemyMesh->SetupAttachment(RootComponent);
	
    Target = nullptr;
    MeleeDamageAmount = 50;
    MovementSpeed = 200;

	MaxAmmo = 5;
	CurrentAmmo = 5;
	ShootingRange = 400.f;

	ShootingDelay = 2.f;
	bCanShoot = true;
	FiringDelayTimer = 0.f;

	ReloadDelay = 7.f;
	bReloading = false;
	ReloadTimer = 0.f;
}

void AEnemyActor::OnEnemyCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, FHitResult const& SweepResult)
{
	if (AA01_PlatformerCharacter* Character = Cast<AA01_PlatformerCharacter>(OtherActor))
	{
		Character->DamagePlayer(MeleeDamageAmount);
		Destroy();
    }
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();

	EnemyMesh->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnEnemyCollision);
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!bReloading)
	{
		ReloadTimer += DeltaTime;
		if (ReloadTimer >= ReloadDelay)
		{
			bCanShoot = true;
			bReloading = false;
			ReloadTimer = 0.f;
		}
    } else if (!bCanShoot)
	{
		FiringDelayTimer += DeltaTime;
		if (FiringDelayTimer >= ShootingDelay)
		{
			bCanShoot = true;
			ReloadTimer = 0.f;
		}
    }

	if (!Target) { return; }

	FVector const OurLocation = GetActorLocation();
	FVector Direction = Target->GetActorLocation() - OurLocation;
	Direction.Normalize();

	if(bCanShoot && FVector::Distance(GetActorLocation(), Target->GetActorLocation()) <= ShootingRange)
    {
		FRotator const ProjectileRot = Direction.Rotation();
		AProjectile* Projectile = Cast<AProjectile>(GetWorld()->SpawnActor(ProjectileClass,
			&OurLocation,
			&ProjectileRot));

		UE_LOG(Enemy, Display, TEXT("Enemy: %s fired projectile at the player"), *GetName());

		Projectile->Parent = this;
		Projectile->DamageAmount = 2.f;
		Projectile->MovementSpeed = 2000.f;
		bCanShoot = false;
		CurrentAmmo -= 1u;

		bReloading = CurrentAmmo == 0u;
    } else if (bReloading) {
		Direction.Z = 0;
		
		FVector NewLocation = OurLocation + (Direction * MovementSpeed * DeltaTime);

		FRotator EnemyRotation = UKismetMathLibrary::MakeRotFromX(Direction);
		EnemyRotation.Pitch = 0;
		EnemyRotation.Roll = 0;
		SetActorLocationAndRotation(NewLocation, EnemyRotation);
	}
}


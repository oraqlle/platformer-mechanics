// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretActor.h"
#include "Projectile.h"

// Sets default values
ATurretActor::ATurretActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
    TurretMesh->SetupAttachment(RootComponent);

	ShootingDelay = 5;
    bCanShoot = true;
    FieldOfView = 45;
    TurretRange = 1000;
}

// Called when the game starts or when spawned
void ATurretActor::BeginPlay()
{
	Super::BeginPlay();

	TurretTarget = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void ATurretActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bCanShoot)
	{
		ReloadTimer += DeltaTime;
		if (ReloadTimer >= ShootingDelay)
		{
			bCanShoot = true;
			ReloadTimer = 0;
		}
    }

	if (!TurretTarget) { return; }
	if (!ProjectileClass) { return; }

	if(bCanShoot && FVector::Distance(GetActorLocation(), TurretTarget->GetActorLocation()) <= TurretRange)
    {
		FVector const Location = GetActorLocation();
		FVector const Forward = GetActorForwardVector();
		FVector Direction = TurretTarget->GetActorLocation() - Location;

		float const RotationAngleRad = FMath::Acos(Forward.Dot(Direction));
		float const RotationAngleDeg = FMath::RadiansToDegrees(RotationAngleRad);

		if (RotationAngleDeg <= FieldOfView)
		{
			Direction.Normalize();
			FRotator const ProjectileRot = Direction.Rotation();
			AProjectile* Projectile = Cast<AProjectile>(GetWorld()->SpawnActor(ProjectileClass,
				&Location,
				&ProjectileRot));

			Projectile->Parent = this;
			bCanShoot = false;
		}
    }
}


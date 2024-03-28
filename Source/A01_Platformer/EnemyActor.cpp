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
    MeleeDamageAmount = 50.f;
    MovementSpeed = 200.f;

	Ammo = 5;
	ShootingRange = 400.f;

	ProjectileDamage = 20.f;
	ProjectileSpeed = 2000.f;

	ShootingDelay = 2.f;
	bCanShoot = true;
	bCanChase = true;
	FiringDelayTimer = 0.f;
}

void AEnemyActor::OnEnemyCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, FHitResult const& SweepResult)
{
	if (AA01_PlatformerCharacter* Character = Cast<AA01_PlatformerCharacter>(OtherActor); Character)
	{
		Character->DamagePlayer(MeleeDamageAmount);
    }

	Destroy();
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
	
	if (!bCanShoot)
	{
		FiringDelayTimer += DeltaTime;
		if (FiringDelayTimer >= ShootingDelay)
		{
			bCanShoot = true;
			FiringDelayTimer = 0.f;
		}
    }

	if (!Target) { return; }

	FVector const OurLocation = GetActorLocation();
	auto const ProjectileSpawnLocation = OurLocation + (50.f * GetActorForwardVector());
	FVector Direction = Target->GetActorLocation() - OurLocation;
	Direction.Normalize();

	if (Ammo > 0 && bCanShoot && FVector::Distance(GetActorLocation(), Target->GetActorLocation()) <= ShootingRange)
    {
		bCanChase = false;
		FRotator const ProjectileRot = Direction.Rotation();
		AProjectile* Projectile = Cast<AProjectile>(GetWorld()->SpawnActor(ProjectileClass,
			&ProjectileSpawnLocation,
			&ProjectileRot));

		UE_LOG(Enemy, Display, TEXT("Enemy: %s fired projectile at the player"), *GetName());

		Projectile->Parent = this;
		Projectile->DamageAmount = ProjectileDamage;
		Projectile->MovementSpeed = ProjectileSpeed;
		bCanShoot = false;
		Ammo -= 1u;
		bCanChase = Ammo == 0;

		UE_LOG(Enemy, Display, TEXT("Enemy: %s has fired projectile at the player"), *GetName());
    } else if (bCanChase) {
		Direction.Z = 0;
		
		FVector NewLocation = OurLocation + (Direction * MovementSpeed * DeltaTime);

		FRotator EnemyRotation = UKismetMathLibrary::MakeRotFromX(Direction);
		EnemyRotation.Pitch = 0;
		EnemyRotation.Roll = 0;
		SetActorLocationAndRotation(NewLocation, EnemyRotation);
	}
}


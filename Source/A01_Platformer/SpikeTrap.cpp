// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikeTrap.h"

// Sets default values
ASpikeTrap::ASpikeTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamagePerSecond = 10;
	CollidingPlayer = nullptr;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	TrapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trap Mesh"));
	TrapMesh->SetupAttachment(RootComponent);
	DamageVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Volume"));
	DamageVolume->SetupAttachment(RootComponent);

	DamageVolume->OnComponentBeginOverlap.AddDynamic(this, &ASpikeTrap::OnDamageBeginOverlap);
	DamageVolume->OnComponentEndOverlap.AddDynamic(this, &ASpikeTrap::OnDamageEndOverlap);
}

// Called when the game starts or when spawned
void ASpikeTrap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpikeTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpikeTrap::OnDamageBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, FHitResult const& SewwpResult)
{
	AA01_PlatformerCharacter* TempCharacter = Cast<AA01_PlatformerCharacter>(OtherActor);

	if (TempCharacter)
	{
		CollidingPlayer = TempCharacter;
		GetWorld()->GetTimerManager().SetTimer(DamageTimer, this, &ASpikeTrap::DamageTime, 1, true);
	}
}

void ASpikeTrap::OnDamageEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == CollidingPlayer)
	{
		GetWorld()->GetTimerManager().ClearTimer(DamageTimer);
		CollidingPlayer = nullptr;
	}
}

void ASpikeTrap::DamageTime()
{
	if (CollidingPlayer)
	{
		CollidingPlayer->DamagePlayer(DamagePerSecond);
	}
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapdoorActor.h"

#include "A01_PlatformerCharacter.h"

// Sets default values
ATrapdoorActor::ATrapdoorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	TrapdoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trapdoor Mesh"));
	TrapdoorTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trapdoor Trigger"));

	TrapdoorMesh->SetupAttachment(RootComponent);
	TrapdoorTrigger->SetupAttachment(RootComponent);

	RotationSpeed = 500;
    CurrentRotation = 0;
    MaxRotation = 90;
    bIsTrapdoorOpen = false;
    TrapdoorDelay= 0.25;
}

void ATrapdoorActor::OnTrapdoorTrigger(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, FHitResult const& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		if(AA01_PlatformerCharacter* Character = Cast<AA01_PlatformerCharacter>(OtherActor); Character) {
			GetWorld()->GetTimerManager().SetTimer(DropTimerHandle,
				this,
				&ATrapdoorActor::OnTrapdoorActivate,
				TrapdoorDelay,
				false);
		}	
	}
}

void ATrapdoorActor::OnTrapdoorActivate()
{
	bIsTrapdoorOpen = true;
}

// Called when the game starts or when spawned
void ATrapdoorActor::BeginPlay()
{
	Super::BeginPlay();

	TrapdoorTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATrapdoorActor::OnTrapdoorTrigger);
}

// Called every frame
void ATrapdoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bIsTrapdoorOpen && CurrentRotation < MaxRotation)
	{
		float RotationAmount = RotationSpeed * DeltaTime;
        CurrentRotation += RotationAmount;

		FRotator NewRotation = FRotator(0,0 , RotationAmount);
        AddActorLocalRotation(NewRotation);
	}
}


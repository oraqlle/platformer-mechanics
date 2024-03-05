// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItem.h"

#include "A01_PlatformerCharacter.h"

// Sets default values
APickupItem::APickupItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &APickupItem::OnOverlap);
}

// Called when the game starts or when spawned
void APickupItem::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = false;
	
	if (!Item)
	{
		Item = NewObject<UItem>();
		Item->SetName("Health");
		Item->SetDescription("A potion to recover lost health");
	}
}

// Called every frame
void APickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupItem::OnOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, FHitResult const& SweepResult)
{
	if (AA01_PlatformerCharacter* Character = Cast<AA01_PlatformerCharacter>(OtherActor); Character)
	{
		if (Character->AddItem(Item))
		{
			Destroy();
		}
	}
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryActorComponent.h"

// Sets default values for this component's properties
UInventoryActorComponent::UInventoryActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	InventorySize = 12;
}


// Called when the game starts
void UInventoryActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

auto UInventoryActorComponent::CreateDefaultItems() -> void
{
	UItem* TempItem = nullptr;
	
	TempItem = NewObject<UItem>();
	TempItem->SetName("Health");
	TempItem->SetDescription("A potion to recover lost health");
	InventoryItems.Add(TempItem);
	
	TempItem = NewObject<UItem>();
	TempItem->SetDescription("A mysterious rune. Said to make you faster for 10 seconds");
	TempItem->SetName("Speed");
	InventoryItems.Add(TempItem);
	
	TempItem = NewObject<UItem>();
	TempItem->SetDescription("A mysterious rune. Said to make you double jump for 10 seconds");
	TempItem->SetName("Jump");
	InventoryItems.Add(TempItem);
	
	TempItem = NewObject<UItem>();
	TempItem->SetDescription("A mysterious rune. Said to freeze time around you for 10 second");
	TempItem->SetName("Freeze");
	InventoryItems.Add(TempItem);
}

auto UInventoryActorComponent::GetAllItems() -> TArray<UItem*>
{
	return InventoryItems;
}

auto UInventoryActorComponent::GetItemAtIndex(int32 Index) -> UItem*
{
	if (Index < 0 || InventoryItems.Num() <= Index)
	{
		return nullptr;
	}
	
	return InventoryItems[Index];
}

auto UInventoryActorComponent::UseItemAtIndex(int32 Index, AA01_PlatformerCharacter* Character) -> bool
{
	return false;
}

auto UInventoryActorComponent::DeleteItemAtIndex(int32 Index) -> bool
{
	
	if (Index < 0 || InventoryItems.Num() <= Index)
	{
		return false;
	}

	InventoryItems.RemoveAt(Index);
	return true;
}

auto UInventoryActorComponent::AddItem(UItem* NewItem) -> bool
{
	
	if (InventorySize <= InventoryItems.Num())
	{
		return false;
	}

	InventoryItems.Add(NewItem);
	return true;
}

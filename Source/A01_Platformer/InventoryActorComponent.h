// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "A01_PlatformerCharacter.h"
#include "Item.h"
#include "Components/ActorComponent.h"
#include "InventoryActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class A01_PLATFORMER_API UInventoryActorComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Inventory")
	int32 InventorySize;

	UPROPERTY()
	TArray<UItem*> InventoryItems;

public:	
	// Sets default values for this component's properties
	UInventoryActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	auto CreateDefaultItems() -> void;
	
public:	

	auto GetAllItems() -> TArray<UItem*>;

	auto GetItemAtIndex(int32 Index) -> UItem*;

	auto UseItemAtIndex(int32 Index, AA01_PlatformerCharacter* Character) -> bool;

	auto DeleteItemAtIndex(int32 Index) -> bool;

	auto AddItem(UItem* NewItem) -> bool;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

UItem::UItem()
{
	ItemName = FString("Default");
	ItemDescription = FString("A default description for a default item. This should never exist in the program");
}

auto UItem::SetName(FString Name) -> void
{
	ItemName = Name;
}

auto UItem::SetDescription(FString Description) -> void
{
	ItemDescription = Description;
}

auto UItem::GetName() -> FString
{
	return ItemName;
}


auto UItem::GetDescription() -> FString
{
	return ItemDescription;
}

void UItem::UseItem(AA01_PlatformerCharacter* Character)
{
	return;
}

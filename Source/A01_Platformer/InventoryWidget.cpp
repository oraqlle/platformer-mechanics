// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "A01_PlatformerCharacter.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"

auto UInventoryWidget::RefreshInventory(TArray<UItem*> Items) -> void
{
	for(auto* Btn : ButtonList)
	{
		Btn->UpdateItemIcon(*ImageMap.Find("None"));
	}
	
	for(auto Idx = 0; Idx < Items.Num(); Idx++)
	{
		ButtonList[Idx]->UpdateItemIcon(*ImageMap.Find(Items[Idx]->GetName()));
	}
}

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (0 < ButtonList.Num()) { return; }

	for(int32 Y = 0; Y < NumButtonHeight; Y++)
	{
		for(int32 X = 0; X < NumButtonWidth; X++)
		{
			FString WidgetName = FString::Printf(TEXT("Button_X%d_Y%x"), X, Y);
			UItemButtonWidget* Button = WidgetTree->ConstructWidget<UItemButtonWidget>(BPButtonWidget, FName(WidgetName));

			ButtonList.Add(Button);
			Button->OnClickedDelegate.AddDynamic(this, &UInventoryWidget::OnButtonWasClicked);
			InventoryGrid->AddChildToGrid(Button, Y, X);
		}
	}
	
	ItemNameTextBlock->SetText(FText::FromString("No Item Selected"));
	ItemDescriptionTextBlock->SetText(FText::FromString("No Item Selected"));

	UseItemButton->OnClicked.AddUniqueDynamic(this, &UInventoryWidget::OnUseButtonClicked);
	DeleteItemButton->OnClicked.AddUniqueDynamic(this, &UInventoryWidget::OnDeleteButtonClicked);
}

void UInventoryWidget::OnButtonWasClicked(UItemButtonWidget* Button)
{
	SelectedItemIndex = ButtonList.Find(Button);
	
	UE_LOG(LogTemp, Warning, TEXT("Button %s, Index %d"), *Button->GetName(), SelectedItemIndex);
	
	if(auto* SelectedItem = Owner->GetItemAtIndex(SelectedItemIndex); SelectedItem)
	{
		ItemNameTextBlock->SetText(FText::FromString(SelectedItem->GetName()));
		ItemDescriptionTextBlock->SetText(FText::FromString(SelectedItem->GetDescription()));
	}
}

void UInventoryWidget::OnUseButtonClicked()
{
	Owner->UseItem(SelectedItemIndex);
	SelectedItemIndex -= 1;
}

void UInventoryWidget::OnDeleteButtonClicked()
{
	Owner->DeleteItemAtIndex(SelectedItemIndex);
	ItemNameTextBlock->SetText(FText::FromString("No Item Selected"));
	ItemDescriptionTextBlock->SetText(FText::FromString("No Item Selected"));
}

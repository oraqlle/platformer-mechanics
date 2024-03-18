// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemButtonWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "Components/TextBlock.h"
#include "InventoryWidget.generated.h"

class UItem;
class AA01_PlatformerCharacter;

/**
 * 
 */
UCLASS()
class A01_PLATFORMER_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UItemButtonWidget> BPButtonWidget;

	UPROPERTY(meta=(BindWidget))
	UGridPanel* InventoryGrid;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ItemNameTextBlock;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ItemDescriptionTextBlock;
	UPROPERTY(meta=(BindWidget))
	UButton* UseItemButton;
	UPROPERTY(meta=(BindWidget))
	UButton* DeleteItemButton;

	UFUNCTION()
	void OnButtonWasClicked(UItemButtonWidget* Button);

	UFUNCTION()
	void OnUseButtonClicked();

	UFUNCTION()
	void OnDeleteButtonClicked();

	AA01_PlatformerCharacter* Owner;

	auto RefreshInventory(TArray<UItem*> Items) -> void;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY()
	TArray<UItemButtonWidget*> ButtonList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, UTexture2D*> ImageMap;

	int32 SelectedItemIndex = -1;
	
	int32 NumButtonWidth = 4;
	int32 NumButtonHeight = 3;

};

// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedBoostItem.h"

#include "A01_PlatformerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

USpeedBoostItem::USpeedBoostItem()
{
	ItemName = "Speed Boost";
	ItemDescription = "A mysterious rune. Said to make you faster";
	SpeedBoostAmount = 100.f;
	SpeedBoostDuration = 1.f;
}

void USpeedBoostItem::UseItem(AA01_PlatformerCharacter* Character)
{
	Super::UseItem(Character);

	if (Character)
	{
		AffectedCharacter = Character;
		AffectedCharacter->GetCharacterMovement()->MaxWalkSpeed += SpeedBoostAmount;
		Character->GetWorld()->GetTimerManager().SetTimer(
			BoostTimer,
			this,
			&USpeedBoostItem::OnSpeedBoostEnd,
			SpeedBoostDuration,
			false);
	}
}

auto USpeedBoostItem::OnSpeedBoostEnd() -> void
{
	if (AffectedCharacter)
	{
		AffectedCharacter->GetCharacterMovement()->MaxWalkSpeed -= SpeedBoostAmount;
		AffectedCharacter = nullptr;
	}
}

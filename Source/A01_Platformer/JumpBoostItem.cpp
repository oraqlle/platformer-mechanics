// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpBoostItem.h"

#include "A01_PlatformerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UJumpBoostItem::UJumpBoostItem()
{
	ItemName = "Jump";
	ItemDescription = "A mysterious rune. Said to make you jump higher";

	JumpBoostAmount = 100.f;
	JumpBoostDuration = 1.f;
}

void UJumpBoostItem::UseItem(AA01_PlatformerCharacter* Character)
{
	Super::UseItem(Character);

	if (Character)
	{
		AffectedCharacter = Character;
		AffectedCharacter->GetCharacterMovement()->JumpZVelocity += JumpBoostAmount;

		Character->GetWorld()->GetTimerManager().SetTimer(
			BoostTimer,
			this,
			&UJumpBoostItem::OnJumpBoostEnd,
			JumpBoostDuration,
			false);
	}
}

auto UJumpBoostItem::OnJumpBoostEnd() -> void
{
	if (AffectedCharacter)
	{
		AffectedCharacter->GetCharacterMovement()->JumpZVelocity -= JumpBoostAmount;
		AffectedCharacter = nullptr;
	}
}

// Copyright Epic Games, Inc. All Rights Reserved.

#include "A01_PlatformerGameMode.h"
#include "A01_PlatformerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AA01_PlatformerGameMode::AA01_PlatformerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

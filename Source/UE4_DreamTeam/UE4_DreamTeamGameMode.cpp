// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE4_DreamTeamGameMode.h"
#include "UE4_DreamTeamCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE4_DreamTeamGameMode::AUE4_DreamTeamGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

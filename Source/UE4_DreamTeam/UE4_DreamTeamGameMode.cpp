// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE4_DreamTeamGameMode.h"
#include "UE4_DreamTeamCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Main.h"
#include "ABPlayerController.h"

AUE4_DreamTeamGameMode::AUE4_DreamTeamGameMode()
{
	DefaultPawnClass = AMain::StaticClass();
	PlayerControllerClass = AABPlayerController::StaticClass();


	// set default pawn class to our Blueprinted character
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/
}

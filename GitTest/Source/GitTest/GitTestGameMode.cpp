// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "GitTest.h"
#include "GitTestGameMode.h"
#include "GitTestHUD.h"
#include "GitTestCharacter.h"

AGitTestGameMode::AGitTestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AGitTestHUD::StaticClass();
}

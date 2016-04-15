// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Shotgun_Prototype.h"
#include "Shotgun_PrototypeGameMode.h"
#include "Shotgun_PrototypeHUD.h"
//#include "Shotgun_PrototypeCharacter.h"

AShotgun_PrototypeGameMode::AShotgun_PrototypeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AShotgun_PrototypeHUD::StaticClass();
}

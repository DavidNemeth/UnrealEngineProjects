// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "UeMinecraft.h"
#include "UeMinecraftGameMode.h"
#include "UeMinecraftHUD.h"
#include "UeMinecraftCharacter.h"

AUeMinecraftGameMode::AUeMinecraftGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AUeMinecraftHUD::StaticClass();
}

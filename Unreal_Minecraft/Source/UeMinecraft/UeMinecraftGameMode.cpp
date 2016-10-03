// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "UeMinecraft.h"
#include "UeMinecraftGameMode.h"
#include "UeMinecraftHUD.h"
#include "UeMinecraftCharacter.h"
#include "Blueprint/UserWidget.h"

void AUeMinecraftGameMode::BeginPlay()
{
	Super::BeginPlay();

	ApplyHUDChanges();
}

AUeMinecraftGameMode::AUeMinecraftGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AUeMinecraftHUD::StaticClass();

	HUDState = EHUDState::HS_Ingame;
}

void AUeMinecraftGameMode::ApplyHUDChanges()
{
	/*remove previous HUD when we apply new one*/
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromParent();
	}

	/*Check the HUD state, and apply the HUD corresponding to the HUD that should be open*/
	switch (HUDState)
	{
	case EHUDState::HS_Ingame:
	{
		ApplyHUD(IngameHUDClass, false, false);
	}
	case EHUDState::HS_Inventory:
	{
		ApplyHUD(InventoryHUDClass, true, true);
	}
	case EHUDState::HS_Craft_Menu:
	{
		ApplyHUD(CraftMenuHUDClass, true, true);
	}
	default:
	{
		ApplyHUD(IngameHUDClass, false, false);
	}
	}
}

uint8 AUeMinecraftGameMode::GetHUDState()
{
	return HUDState;
}

void AUeMinecraftGameMode::ChangeHUDState(uint8 NewState)
{
	HUDState = NewState;
	ApplyHUDChanges();
}

bool AUeMinecraftGameMode::ApplyHUD(TSubclassOf<class UUserWidget> WidgetToApply, bool ShowMouseCursor, bool EnableClickEvents)
{
	/*reference to the player, and the player controller*/
	AUeMinecraftCharacter* MyCharacter = Cast<AUeMinecraftCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	APlayerController* MyController = GetWorld()->GetFirstPlayerController();

	/*Null check the widget before applying it*/
	if (WidgetToApply != nullptr)
	{
		/*set mouse events and visibility according the parameters taken by the function*/
		MyController->bShowMouseCursor = ShowMouseCursor;
		MyController->bEnableClickEvents = EnableClickEvents;

		/*create widget*/
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetToApply);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
			return true;
		}
		else
			return false;		
	}
	else
			return false;
}

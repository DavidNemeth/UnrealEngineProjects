// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "InventorySystem.h"
#include "InventorySystemGameMode.h"
#include "InventorySystemHUD.h"
#include "InventorySystemCharacter.h"
#include "Blueprint/UserWidget.h"

void AInventorySystemGameMode::BeginPlay()
{
	/*As soon as game starts, apply HUD to the screen*/
	ApplyHUDChanges();
}

AInventorySystemGameMode::AInventorySystemGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AInventorySystemHUD::StaticClass();

	/*Set default HUD-state*/
	HUDState = EHUDState::HS_Ingame;
}

void AInventorySystemGameMode::ApplyHUDChanges()
{

	/*Remove the previous HUD, since we are applying a new one*/
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromParent();
	}

	switch (HUDState)
	{
		case EHUDState::HS_Ingame:
		{
			ApplyHUD(IngameHUDClass, false, false);
			break;
		}
		case EHUDState::HS_Inventory:
		{
			ApplyHUD(inventoryHUDClass, true, true);
			break;
		}
		case EHUDState::HS_Shop_General:
		{
			ApplyHUD(ShopGeneralHUDClass, true, true);
			break;
		}
		default:
		{
			ApplyHUD(IngameHUDClass, false, false);
			break;
		}
	}
}

uint8 AInventorySystemGameMode::GetHUDState()
{
	return HUDState;
}

void AInventorySystemGameMode::ChangeHUDState(uint8 NewState)
{
	HUDState = NewState;
	ApplyHUDChanges();
}

bool AInventorySystemGameMode::ApplyHUD(TSubclassOf<class UUserWidget> WidgetToApply, bool bShowMouseCursor, bool EnableClickEvents)
{
	/*Player and controller reference*/
	AInventorySystemCharacter* MyCharacter = Cast<AInventorySystemCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	APlayerController* MyController = GetWorld()->GetFirstPlayerController();

	/*Null-check widget we are trying to apply*/
	if (WidgetToApply != nullptr)
	{
		/*Set mouse visibility and click events according to params*/
		MyController->bShowMouseCursor = bShowMouseCursor;
		MyController->bEnableClickEvents = EnableClickEvents;

		/*Create the widgets*/
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetToApply);

		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
			return true;
		}
		else return false;
	}
	else return false;
}

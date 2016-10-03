// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "UeMinecraftGameMode.generated.h"

UCLASS(minimalapi)
class AUeMinecraftGameMode : public AGameMode
{
	GENERATED_BODY()

		virtual void BeginPlay() override;

public:
	AUeMinecraftGameMode();

	enum EHUDState : uint8
	{
		HS_Ingame,
		HS_Inventory,
		HS_Craft_Menu,
	};

	/*checks the HUD state, and calls the apply HUD to apply*/
	void ApplyHUDChanges();

	/*gets the HUD state*/
	uint8 GetHUDState();

	/*setter for the HUD state*/
	UFUNCTION(BlueprintCallable, Category = "HUD Functions")
		void ChangeHUDState(uint8 NewState);

	/*apply HUD to the screen, return true if successful*/
	bool ApplyHUD(TSubclassOf<class UUserWidget> WidgetToApply, bool ShowMouseCursor, bool EnableClickEvents);

protected:

	/*The current HUD state*/
	uint8 HUDState;

	/*the HUD to be shown in-game*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Blueprints Widgets", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> IngameHUDClass;

		/*the HUD to be shown in the inventory*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Blueprints Widgets", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> InventoryHUDClass;

		/*the HUD to be shown in the crafting menu*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Blueprints Widgets", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> CraftMenuHUDClass;

	/*the current HUD*/
	class UUserWidget* CurrentWidget;
};




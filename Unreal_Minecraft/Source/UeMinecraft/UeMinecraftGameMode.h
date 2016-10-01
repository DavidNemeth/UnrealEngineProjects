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

	/*checks the HUD state, and calls the applyhud to apply*/
	void ApplyHUDChanges();

	/*gets the hud state*/
	uint8 GetHUDState();

	/*setter for the hudstate*/
	UFUNCTION(BlueprintCallable, Category = "HUD Functions")
		void ChangeHUDState(uint8 NewState);

	/*apply hud to the screen, return true if successful*/
	bool ApplyHUD(TSubclassOf<class UUserWidget> WidgetToApply, bool ShowMouseCursor, bool EnableClickEvents);

protected:

	/*The current hudstate*/
	uint8 HUDState;

	/*the hud to be shown ingame*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Blueprints Widgets", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> IngameHUDClass;

		/*the hud to be shown in the inventory*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Blueprints Widgets", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> InventoryHUDClass;

		/*the hud to be shown in the crafting menu*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Blueprints Widgets", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> CraftMenuHUDClass;

	/*the current hud*/
	class UUserWidget* CurrentWidget;
};




// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "InventorySystemGameMode.generated.h"

UCLASS(minimalapi)
class AInventorySystemGameMode : public AGameMode
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

public:
	AInventorySystemGameMode();

	enum EHUDState : uint8
	{
		HS_Ingame,
		HS_Inventory,
		HS_Shop_General,
		HS_Shop_Weapon
	};

	/*Checks the HUD state, and calls applyHUD to apply proper HUD*/
	void ApplyHUDChanges();

	/*Getter for HUD-state*/
	uint8 GetHUDState();

	/*Setter for HUD-state*/
	UFUNCTION(BlueprintCallable, Category = "HUD Functions")
		void ChangeHUDState(uint8 NewState);

	/*Apply a HUD, returns true if successful, false otherwise*/
	bool ApplyHUD(TSubclassOf<class UUserWidget> WidgetToApply, bool bShowMouseCursor, bool EnableClickEvents);

protected:

	uint8 HUDState;

	/*The HUD to be shown in-game*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUDWidgets", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> IngameHUDClass;

	/*The HUD to be shown in the inventory*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUDWidgets", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> inventoryHUDClass;

	/*The HUD to be shown in the shop*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUDWidgets", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> ShopGeneralHUDClass;

	UPROPERTY()
		class UUserWidget* CurrentWidget;
};




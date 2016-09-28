// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "UeMinecraftHUD.generated.h"

UCLASS()
class AUeMinecraftHUD : public AHUD
{
	GENERATED_BODY()

public:
	AUeMinecraftHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};


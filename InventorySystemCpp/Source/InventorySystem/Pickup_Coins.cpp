// Fill out your copyright notice in the Description page of Project Settings.

#include "InventorySystem.h"
#include "InventorySystemCharacter.h"
#include "Pickup_Coins.h"

APickup_Coins::APickup_Coins()
{
	AmountOfCoins = 0;
}

void APickup_Coins::Interact_Implementation()
{

	AInventorySystemCharacter* Character = Cast<AInventorySystemCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	Character->UpdateGold(AmountOfCoins);

	Destroy();
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "InventorySystem.h"
#include "Pickup.h"
#include "InventorySystemCharacter.h"

APickup::APickup()
{
	/*Set up the mesh for pickup,and set the item name, help text and item value*/
	InteractableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	InteractableMesh->SetSimulatePhysics(true);

	ItemName = FString("Enter an item name here");
	InteractableHelpText = FString("Press E to pick item up.");
	Value = 0;
}

void APickup::BeginPlay()
{
	InteractableHelpText = FString::Printf(TEXT("%s: Press E to pick up."), *ItemName);
}

void APickup::Interact_Implementation()
{

	AInventorySystemCharacter* Character = Cast<AInventorySystemCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	/*Put code here that places the item into the characters inventory*/

	OnPickedUp();

}

void APickup::Use_Implementation()
{
	GLog->Log("Use() from base pickup class: YOU SHOULD NOT BE SEEING THIS");
}

void APickup::OnPickedUp()
{
	InteractableMesh->SetVisibility(false);
	InteractableMesh->SetSimulatePhysics(false);
	InteractableMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

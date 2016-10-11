// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

UCLASS()
class INVENTORYSYSTEM_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	


	UFUNCTION(BlueprintNativeEvent)
		void Interact();
	virtual void Interact_Implementation();
	
	/*Mesh for Interaction*/
	UPROPERTY(EditAnywhere, Category = "Intractable Properties")
		class UStaticMeshComponent* InteractableMesh;

	/*Help text to interact in game*/
	UPROPERTY(EditAnywhere, Category = "Intractable Properties")
		FString InteractableHelpText;

};

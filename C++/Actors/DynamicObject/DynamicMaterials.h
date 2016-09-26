// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DynamicMaterials.generated.h"

UCLASS()
class BASICS_API ADynamicMaterials : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADynamicMaterials();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//Dummy root component for the cube
	UPROPERTY(EditAnywhere)
		USceneComponent* CubeRoot;

	//Mesh for the cure
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* CubeMesh;

	//trigger for the cube
	UPROPERTY(EditAnywhere)
		UBoxComponent* CubeTrigger;

	//function called when the player triggers the Rust effect
	UFUNCTION()
		void OnPlayerTriggerRust(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	//function called when the player untriggers the rust effect
	UFUNCTION()
		void OnPlayerExitRust(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:

	bool bRustEffectTriggered;
	
	float RustAmount;
};

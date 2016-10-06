// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Rotatable.generated.h"

UCLASS()
class LEVELDESIGNS_API ARotatable : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARotatable();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	/*The axis to rotate the mesh on*/
	UPROPERTY(EditAnywhere)
		FString RotationAxis = "Yaw";

	/*The static mesh for the rotatable*/
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* RotatableMesh;

	/*The box trigger for the rotatable*/
	UPROPERTY(EditDefaultsOnly)
		UBoxComponent* AnimTrigger;

	/*Maximum spin rotatable will reach*/
	UPROPERTY(EditAnywhere, Category = "Animation")
		float MaxRotation;

	/*Curve float reference*/
	UPROPERTY(EditAnywhere, Category = "Animation")
		UCurveFloat* AnimCurve;

private:

	/*Initial rotation*/
	FRotator ActorInitialRotation;

	/*Target rotation*/
	FRotator TargetRotation;

	/*Time-line to make rotatable spin*/
	FTimeline MyTimeline;

	UFUNCTION()
		void HandleProgress(float Value);

	UFUNCTION()		
		void OnAnimTriggered(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DodgeActor.generated.h"

UCLASS()
class BASICS_API ADodgeActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADodgeActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
		UShapeComponent* Box;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MyMesh;

	UPROPERTY(EditAnywhere)
		float SpeedScale;

	FVector PlayerStartingLocation = FVector(3566.0f, 3.0f, 232.0f);

	FVector BoxSize = FVector(1.5f, 1.5f, 1.5f);

	float RunningTime;

	UFUNCTION()
		void TriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditAnywhere)
		bool bMovesYAxes = true;

	UPROPERTY(EditAnywhere)
		USoundBase *MySound;

};

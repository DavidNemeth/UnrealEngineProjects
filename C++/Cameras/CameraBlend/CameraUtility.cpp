// Fill out your copyright notice in the Description page of Project Settings.

#include "Basics.h"
#include "CameraUtility.h"

// Sets default values
ACameraUtility::ACameraUtility()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraUtility::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACameraUtility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float TimeBetweenCameraChanges = 5.0f;
	const float SmoothBlendTime = 2.0f;

	TimeToNextCameraChange -= DeltaTime;

	if (TimeToNextCameraChange <= 0.0f)
	{
		TimeToNextCameraChange += TimeBetweenCameraChanges;

		APlayerController* OurPlayer = UGameplayStatics::GetPlayerController(this, 0);

		if (OurPlayer)
		{
			if (CameraTwo && (OurPlayer->GetViewTarget() == CameraOne))
			{
				OurPlayer->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
			}
			else if (CameraOne)
			{
				OurPlayer->SetViewTarget(CameraOne);
			}
		}
	}



}


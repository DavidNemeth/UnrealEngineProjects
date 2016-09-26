// Fill out your copyright notice in the Description page of Project Settings.

#include "Basics.h"
#include "DynamicMaterials.h"


// Sets default values
ADynamicMaterials::ADynamicMaterials()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CubeRoot = CreateDefaultSubobject<USceneComponent>(TEXT("CubeRoot"));
	RootComponent = CubeRoot;

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	CubeMesh->AttachToComponent(CubeRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	CubeTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("CubeTrigger"));
	CubeTrigger->bGenerateOverlapEvents = true;
	CubeTrigger->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	CubeTrigger->OnComponentBeginOverlap.AddDynamic(this, &ADynamicMaterials::OnPlayerTriggerRust);
	CubeTrigger->OnComponentEndOverlap.AddDynamic(this, &ADynamicMaterials::OnPlayerExitRust);
	CubeTrigger->AttachToComponent(CubeRoot,FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	RustAmount = 1.0f;
}

// Called when the game starts or when spawned
void ADynamicMaterials::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADynamicMaterials::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRustEffectTriggered)
	{
		if (RustAmount > 0.0f)
		{
			RustAmount -= DeltaTime;
		}
	}
	if (!bRustEffectTriggered)
	{
		if (RustAmount < 1.0f)
		{
			RustAmount += DeltaTime;
		}
	}

	UMaterialInstanceDynamic* RustMaterialInstance = CubeMesh->CreateDynamicMaterialInstance(0);
	if (RustMaterialInstance != nullptr)
	{
		RustMaterialInstance->SetScalarParameterValue(FName("RustAmount"), RustAmount);
	}
}

void ADynamicMaterials::OnPlayerTriggerRust(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	bRustEffectTriggered = true;
}

void ADynamicMaterials::OnPlayerExitRust(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	bRustEffectTriggered = false;
}


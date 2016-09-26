// Fill out your copyright notice in the Description page of Project Settings.

#include "Basics.h"
#include "DodgeActor.h"


// Sets default values
ADodgeActor::ADodgeActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->bGenerateOverlapEvents = true;
	Box->OnComponentBeginOverlap.AddDynamic(this, &ADodgeActor::TriggerEnter);
	//Box->SetRelativeScale3D(BoxSize);
	RootComponent = Box;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	MyMesh->AttachTo(RootComponent);

	SpeedScale = 0.0f;
}

// Called when the game starts or when spawned
void ADodgeActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADodgeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));

	if (bMovesYAxes)
		NewLocation.Y += DeltaHeight * SpeedScale;
	else
		NewLocation.X += DeltaHeight * SpeedScale;

	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);
}

void ADodgeActor::TriggerEnter(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// teleport back when hit
	if (OtherActor->IsA(ACharacter::StaticClass())) 
	{
		UGameplayStatics::PlaySoundAttached(MySound, OtherActor->GetRootComponent());
		OtherActor->SetActorLocation(PlayerStartingLocation);
	}		
}


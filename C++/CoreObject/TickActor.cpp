// Fill out your copyright notice in the Description page of Project Settings.

#include "Basics.h"
#include "TickActor.h"


// Sets default values
ATickActor::ATickActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));

	RootComponent = Root;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	MyMesh->AttachTo(RootComponent);

}

// Called when the game starts or when spawned
void ATickActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATickActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	FVector NewLocation = GetActorLocation();
}


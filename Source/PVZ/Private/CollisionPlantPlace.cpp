// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionPlantPlace.h"



// Sets default values
ACollisionPlantPlace::ACollisionPlantPlace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetCollisionProfileName(TEXT("PlaceableArea"));
	CollisionComponent->SetCapsuleSize(60.0f, 60.0f);
	RootComponent = CollisionComponent;
}

// Called when the game starts or when spawned
void ACollisionPlantPlace::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollisionPlantPlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


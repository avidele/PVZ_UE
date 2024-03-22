// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantPlaceArea.h"

// Sets default values
APlantPlaceArea::APlantPlaceArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PlacementBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PlacementBox"));
	RootComponent = PlacementBox;
}

// Called when the game starts or when spawned
void APlantPlaceArea::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlantPlaceArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APlantPlaceArea::IsOccupied() const
{
	return PlantedPlant != nullptr;
}

FVector APlantPlaceArea::GetPlacementLocation() const
{
	return PlacementBox->GetComponentLocation();
}
void APlantPlaceArea::Occupy(APaperZDCharacterBase* Plant)
{
	if (!IsOccupied())
	{
		PlantedPlant = Plant;
	}
}

void APlantPlaceArea::NotOccupy()
{
	PlantedPlant = nullptr;
}
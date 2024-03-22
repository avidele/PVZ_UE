// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Plant/PaperZDCharacterBase.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PlantPlaceArea.generated.h"

UCLASS()
class PVZ_API APlantPlaceArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlantPlaceArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* PlacementBox;

	UPROPERTY()
	APaperZDCharacterBase* PlantedPlant;

public:
	bool IsOccupied() const;
	FVector GetPlacementLocation() const;
	void Occupy(APaperZDCharacterBase* Plant);
	void NotOccupy();
};

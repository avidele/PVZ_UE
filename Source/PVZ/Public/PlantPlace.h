// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperTileMapComponent.h"
#include "PaperTileMap.h"
#include "Plant/PaperZDCharacterBase.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PlantPlace.generated.h"

UCLASS()
class PVZ_API APlantPlace : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlantPlace();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TileMap")
	UPaperTileMapComponent* TileMapComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileMap")
	TArray<bool> CanPlaceArray;

	UFUNCTION(BlueprintCallable, Category = "TileMap")
	bool CanPlacePlantAt(const FVector& WorldPosition);

// private:
// 	void InitCanPlaceArray(FName Plant);
// 	APaperZDCharacterBase* PreviewPlant;
//
// public:
// 	UPROPERTY(EditAnywhere)
// 	TSubclassOf<APaperZDCharacterBase> PlantClass;
// 	// Called every frame
// 	virtual void Tick(float DeltaTime) override;
// 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
// 	UBoxComponent* BoxComponent;
//
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plant Slot")
// 	bool bIsOccupied;
//
// 	UFUNCTION(BlueprintCallable, Category = "Plant Slot")
// 	bool CanPlacePlant() const;
//
// 	UFUNCTION(BlueprintCallable, Category = "Plant Slot")
// 	void OnPlantPlaced();
//
// 	UFUNCTION()
// 	void OnMouseEnter(UPrimitiveComponent* TouchedComponent);
//
// 	// Function to call when the mouse is clicked on the box component
// 	UFUNCTION()
// 	void OnMouseClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
//
// 	UFUNCTION()
// 	void OnMouseLeave(UPrimitiveComponent* TouchedComponent);
};

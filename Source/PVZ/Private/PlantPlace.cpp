// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantPlace.h"

#include "PlantPlayerController.h"


// Sets default values
APlantPlace::APlantPlace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TileMapComponent = CreateDefaultSubobject<UPaperTileMapComponent>(TEXT("TileMapComponent"));
	RootComponent = TileMapComponent;
	// BoxComponent= CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	// RootComponent = BoxComponent;
	// BoxComponent->OnBeginCursorOver.AddDynamic(this, &APlantPlace::OnMouseEnter);
	// BoxComponent->OnClicked.AddDynamic(this, &APlantPlace::OnMouseClicked);
	// BoxComponent->OnEndCursorOver.AddDynamic(this, &APlantPlace::OnMouseLeave);
	// bIsOccupied = false;
}

// Called when the game starts or when spawned
void APlantPlace::BeginPlay()
{
	Super::BeginPlay();
	// APlantPlayerController* PlayerController = Cast<APlantPlayerController>(GetWorld()->GetFirstPlayerController());
	// if (PlayerController)
	// {
	// 	PlayerController->OnMyMouseClickedDelegate.AddUObject(this, &APlantPlace::InitCanPlaceArray);
	// }
}

// Called every frame
void APlantPlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APlantPlace::CanPlacePlantAt(const FVector& WorldPosition)
{
	FVector LocalPosition = GetTransform().InverseTransformPosition(WorldPosition);
	int32 MapWidth;
	int32 MapHeight;
	int32 NumLayers;
	TileMapComponent->GetMapSize(MapWidth,MapHeight,NumLayers);
	float TileWidth = TileMapComponent->TileMap->TileWidth;
	float TileHeight = TileMapComponent->TileMap->TileHeight;
	int32 TileX = FMath::FloorToInt(LocalPosition.X / TileWidth);
	int32 TileY = FMath::FloorToInt(LocalPosition.Y / TileHeight);
	if (TileX >= 0 && TileX < MapWidth && TileY >= 0 && TileY < MapHeight)
	{
	
		return true;
	}

	return false;
}

// void APlantPlace::InitCanPlaceArray(FName Plant)
// {
// }


// bool APlantPlace::CanPlacePlantAt(int32 TileX, int32 TileY)
// {
// 	int32 W,H,L;
// 	TileMapComponent->GetMapSize(W,H,L) ;
// 	int32 Index = TileY * W + TileX;
// 	return CanPlaceArray.IsValidIndex(Index) && CanPlaceArray[Index];
// }

// bool APlantPlace::CanPlacePlant() const
// {
// 	return !bIsOccupied;
// }
//
// void APlantPlace::OnPlantPlaced()
// {
// 	bIsOccupied = true;
// }
//
// void APlantPlace::OnMouseEnter(UPrimitiveComponent* TouchedComponent)
// {
// 	if(PlantClass != nullptr)
// 	{
// 		// Get the center of the box component
// 		FVector Center = BoxComponent->GetComponentLocation();
// 		Center.Z = 0;
// 		// Spawn the plant at the center of the box
// 		PreviewPlant = GetWorld()->SpawnActor<APaperZDCharacterBase>(PlantClass, Center, FRotator::ZeroRotator);
//
// 		// You might want to store a reference to the spawned plant here,
// 		// so you can interact with it later or destroy it when necessary.
// 	}
// }
//
// void APlantPlace::OnMouseClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
// {
// 	if(PlantClass != nullptr && PreviewPlant != nullptr)
// 	{
// 		FVector PlacementLocation = PreviewPlant->GetActorLocation();
//         
// 		
// 		PreviewPlant->Destroy();
// 		PreviewPlant = nullptr;
//
// 		
// 		AActor* PlacedPlant = GetWorld()->SpawnActor<AActor>(PlantClass, PlacementLocation, FRotator::ZeroRotator);
// 		if(PlacedPlant != nullptr)
// 		{
// 			
// 			PlacedPlant->SetActorScale3D(FVector(0.02f, 0.02f, 0.02f));
// 		}
// 	}
// }
//
// void APlantPlace::OnMouseLeave(UPrimitiveComponent* TouchedComponent)
// {
// 	if(PreviewPlant != nullptr)
// 	{
// 		PreviewPlant->Destroy();
// 		PreviewPlant = nullptr;
// 	}
// }
//

// Fill out your copyright notice in the Description page of Project Settings.


#include "Plant/PVZGameModeBase.h"
#include "User/PlayerSaveGame.h"
#include "PlantPlayerController.h"
#include "Data/PlantDataStructure.h"
#include "GameInstance/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

APVZGameModeBase::APVZGameModeBase()
{
	GameWinDelegate.AddDynamic(this, &APVZGameModeBase::OnGameWin);
}

// void APVZGameModeBase::Spawn2DCharacter()
// {
// 	if (PaperZDCharacter)
// 	{
// 		FVector SpawnLocation = FVector(0.0f, 0.0f, 0.0f); 
// 		FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f); 
// 		 SpawnedCharacter = GetWorld()->SpawnActor<APaperZDCharacterBase>(PaperZDCharacter, SpawnLocation, SpawnRotation);
// 		FVector NewScale = FVector(0.02f, 0.02f, 0.02f);
// 		 SpawnedCharacter->SetActorScale3D(NewScale);
// 	}
// }
//
// void APVZGameModeBase::DestroyPlant(APaperZDCharacterBase* PlantToDelete)
// {
// 	if (PlantToDelete)
// 	{
// 		PlantToDelete->Destroy();
// 	}
// }

void APVZGameModeBase::BeginPlay()
{
	// MyPlantDataTableBase* PlantDataTable;
	// if (PlantDataTable)
	// {
	// 	FPlantStructureBase* Row = PlantDataTable->FindRow<FPlantStructureBase>(TEXT("Peashooter"), TEXT("Peashooter"),true);
	// 	if (Row)
	// 	{
	// 		
	// 	}
	// }
	Super::BeginPlay();
}

UPlayerSaveGame* APVZGameModeBase::GetLoadedSaveGame() const
{
	APlantPlayerController* PlantPlayerController = Cast<APlantPlayerController>( GetWorld()->GetFirstPlayerController());
	FString CurrentName = PlantPlayerController->GetCurrentPlayerName();
	UPlayerSaveGame* SaveGame = Cast<UPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot(CurrentName, 0));
	if (SaveGame)
	{
		return SaveGame;
	}
	return nullptr;
}

void APVZGameModeBase::OnGameWin(int32 currentLevelNum)
{	FString CurrentName;
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		CurrentName = GameInstance->CurrentName;
	}
	UPlayerSaveGame* SaveGame = Cast<UPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot(CurrentName, 0));
	if (SaveGame)
	{
		SaveGame->UserGold += GoldNum;
		SaveGame->PlayerScore += PlayerScore;
		if (currentLevelNum == 1 || currentLevelNum ==2)
		{
			SaveGame->UnlockedLevelNum = currentLevelNum + 1;
		}
		UGameplayStatics::SaveGameToSlot(SaveGame, CurrentName, 0);
	}
}





#include "GameInstance/MyGameInstance.h"

#include "PlantPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UMyGameInstance::Init()
{
	Super::Init();
	if(FParse::Value(FCommandLine::Get(),TEXT("username="),CurrentName))
	{
		CreateLoad(CurrentName);
		LoadSelectedSaveGame(CurrentName);
	}
	else
	{
		CurrentName = TEXT("DefaultPlayerSave");
	}
	FString DefaultSaveSlot = TEXT("DefaultPlayerSave");

	if (UGameplayStatics::DoesSaveGameExist(DefaultSaveSlot, 0))
	{
		UE_LOG(LogTemp, Log, TEXT("Save game exists. Loading..."));
	}
	else
	{
		UPlayerSaveGame* DefaultSaveGame = Cast<UPlayerSaveGame>(UGameplayStatics::CreateSaveGameObject(UPlayerSaveGame::StaticClass()));
		DefaultSaveGame->PlayerName = TEXT("DefaultPlayer");
		DefaultSaveGame->PlayerPassword = TEXT("DefaultPassword"); 
		DefaultSaveGame->UserGold = 300; 
		DefaultSaveGame->UnlockedPlants = {TEXT("Sunflower"), TEXT("Peashooter")}; 
		UGameplayStatics::SaveGameToSlot(DefaultSaveGame, DefaultSaveSlot, 0);
		UE_LOG(LogTemp, Log, TEXT("Default save game created."));
	}
}

TArray<FString> UMyGameInstance::GetAllSaveGameSlots()
{
	TArray<FString> SaveSlots;
	IFileManager& FileManager = IFileManager::Get();
	// Change the directory path if necessary
	FString SaveDirectory = FPaths::ProjectSavedDir() + TEXT("SaveGames/");
	FString Extension = TEXT("*.sav");

	// Find all files in the directory with the .sav extension
	FileManager.FindFiles(SaveSlots, *SaveDirectory, *Extension);
	// Extract the slot names without extension
	for (FString& Slot : SaveSlots)
	{
		Slot = FPaths::GetBaseFilename(Slot);
	}
	return SaveSlots;
}

bool UMyGameInstance::LoadSelectedSaveGame(const FString& SelectedSlot)
{
	if (UGameplayStatics::DoesSaveGameExist(SelectedSlot, 0))
	{
		CurrentName = SelectedSlot;
		UPlayerSaveGame* SaveGameInstance = Cast<UPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot(SelectedSlot, 0));
		// Assuming 'PlayerName' is the variable you want to display in UMG
		if (SaveGameInstance)
		{
			APlantPlayerController* PlantPlayerController = Cast<APlantPlayerController>(GetWorld()->GetFirstPlayerController());
			if (PlantPlayerController)
			{
				PlantPlayerController->SetCurrentPlayerName(SelectedSlot);
				PlantPlayerController->LoadGame();
			}
			// Do something with the loaded save game, like updating the UI
			return true;
		}
	}
	return false;
}

void UMyGameInstance::CreateLoad(FString LoadName)
{
	if (UGameplayStatics::DoesSaveGameExist(LoadName, 0))
	{
		
		UE_LOG(LogTemp, Log, TEXT("Save game exists. Loading..."));
	}
	else
	{
		UPlayerSaveGame* DefaultSaveGame = Cast<UPlayerSaveGame>(UGameplayStatics::CreateSaveGameObject(UPlayerSaveGame::StaticClass()));
		DefaultSaveGame->PlayerName = LoadName;
		DefaultSaveGame->PlayerPassword = TEXT("DefaultPassword"); 
		DefaultSaveGame->UserGold = 100; 
		DefaultSaveGame->UnlockedPlants = {TEXT("Sunflower"), TEXT("Peashooter")}; 
		UGameplayStatics::SaveGameToSlot(DefaultSaveGame, LoadName, 0);
		UE_LOG(LogTemp, Log, TEXT("%s save game created."),*LoadName);
	}
}

int32 UMyGameInstance::GetPlayerGold() const
{
	UPlayerSaveGame* SaveGame = Cast<UPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot(CurrentName, 0));
	if (SaveGame)
	{
		return SaveGame->UserGold;
	}
	UE_LOG(LogTemp, Log, TEXT("Cant Find Slot"));
	return 0; // Return 0 if the save game doesn't exist or the cast failed
}

TMap<FString,int> UMyGameInstance::GetPlayerRank() const
{
	TMap<FString,int> ScoreDataMap;
	TArray<FString> SaveSlots = GetAllSaveGameSlots();

	for (const FString& Slot : SaveSlots)
	{
		UPlayerSaveGame* LoadedGame = Cast<UPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot(Slot, 0));
		if (LoadedGame)
		{
			ScoreDataMap.Add(Slot,LoadedGame->PlayerScore);
		}
	}
	ScoreDataMap.ValueSort([](const int& A, const int& B) {
		return A > B;
	});
	return ScoreDataMap;
}

int32 UMyGameInstance::GetPlayerRankNum() const
{
	TMap<FString,int> ScoreDataMap = GetPlayerRank();
	int32 RankNum = 1;
	for (const auto& Elem : ScoreDataMap)
	{
		if (Elem.Key == CurrentName)
		{
			return RankNum;
		}
		RankNum++;
	}
	return 0;
}

float UMyGameInstance::GetPlayerScore() const
{
	UPlayerSaveGame* SaveGame = Cast<UPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot(CurrentName, 0));
	if (SaveGame)
	{
		return SaveGame->PlayerScore;
	}
	UE_LOG(LogTemp, Log, TEXT("Cant Find Slot"));
	return 0;
}

int32 UMyGameInstance::GetPlayerLevel() const
{
	UPlayerSaveGame* SaveGame = Cast<UPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot(CurrentName, 0));
	if (SaveGame)
	{
		return SaveGame->UnlockedLevelNum;
	}
	UE_LOG(LogTemp, Log, TEXT("Cant Find Slot"));
	return 0;
}

UPlayerSaveGame* UMyGameInstance::GetSaveGame() const
{
	UPlayerSaveGame* SaveGame = Cast<UPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot(CurrentName, 0));
	if (SaveGame)
	{
		return SaveGame;
	}
	return nullptr;
}

void UMyGameInstance::DeleteGameLoad(FString LoadName)
{
	if (UGameplayStatics::DoesSaveGameExist(LoadName, 0))
	{
		UGameplayStatics::DeleteGameInSlot(LoadName, 0);
	}
}

#include "User/PlayerSaveGame.h"

#include "PlantPlayerController.h"
#include "Kismet/GameplayStatics.h"

UPlayerSaveGame::UPlayerSaveGame()
{
	UnlockedLevelNum = 1;
	UserGold = 100;
	UnlockedPlants = { TEXT("Sunflower"), TEXT("Peashooter") };
}

UPlayerSaveGame* UPlayerSaveGame::RegisterNewPlayer(const FString& Username, const FString& Password)
{
	if (UGameplayStatics::DoesSaveGameExist(Username, 0))
	{
		return nullptr;
	}

	UPlayerSaveGame* NewPlayerSave = Cast<UPlayerSaveGame>(UGameplayStatics::CreateSaveGameObject(UPlayerSaveGame::StaticClass()));
	NewPlayerSave->PlayerName = Username;
	NewPlayerSave->PlayerPassword = Password; 
	NewPlayerSave->UserGold = 100; 
	NewPlayerSave->UnlockedPlants = { TEXT("Sunflower"), TEXT("Peashooter") };

	if (UGameplayStatics::SaveGameToSlot(NewPlayerSave, Username, 0))
	{
		return NewPlayerSave;
	}
	return nullptr;
}

UPlayerSaveGame* UPlayerSaveGame::LoginPlayer(const FString& Username, const FString& Password)
{
	if (UGameplayStatics::DoesSaveGameExist(Username, 0))
	{
		UPlayerSaveGame* LoadedPlayerSave = Cast<UPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot(Username, 0));
		if (LoadedPlayerSave && LoadedPlayerSave->PlayerPassword == Password)
		{
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GWorld, 0);
			if (PlayerController)
			{
				APlantPlayerController* PlantPlayerController = Cast<APlantPlayerController>(PlayerController);
				PlantPlayerController->SetCurrentPlayerName(Username);
				UE_LOG(LogTemp,Display,TEXT("Login Succeed:%s"),*Username);
			}
			return LoadedPlayerSave;
		}
	}
	return nullptr;
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantPlayerController.h"

#include "CollisionPlantPlace.h"
#include "EngineUtils.h"
#include "PlantPlace.h"
#include "PlantPlaceArea.h"
#include "Components/BoxComponent.h"
#include "Data/PlantDataStructure.h"
#include "GameFramework/PlayerState.h"
#include "GameInstance/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Plant/PVZGameModeBase.h"
#include "Sunlight/SunToken.h"
#include "User/PlayerSaveGame.h"


void APlantPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	// if (EnhancedInputComponent)
	// {
	// 	EnhancedInputComponent->BindAction(MyInputAction, ETriggerEvent::Pressed, this, &APlantPlayerController::OnMouseClicked);
	// }
	InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &APlantPlayerController::OnMouseClicked);
	//DefaultMouseCursor = EMouseCursor::Crosshairs;
}


void APlantPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		CurrentPlayerName = GameInstance->CurrentName;
	}
	LoadGame();
}

void APlantPlayerController::OnMouseClicked()
{
	if (!bStartGame)
	{
		return;
	}
	FHitResult HitResult;
	FVector2D MouseScreenPosition;
	APawn* MyPawn = GetPawn();
	if (GetMousePosition(MouseScreenPosition.X, MouseScreenPosition.Y))
	{
			FVector WorldLocation;
			FVector WorldDirection;
			DeprojectScreenPositionToWorld(MouseScreenPosition.X, MouseScreenPosition.Y, WorldLocation, WorldDirection);

			FVector End = ((WorldDirection * 10000.f) + WorldLocation); 
			FCollisionQueryParams CollisionParams;
			CollisionParams.AddIgnoredActor(MyPawn);  // Ignore Pawn

			if (GetWorld()->LineTraceSingleByChannel(HitResult, WorldLocation, End, ECC_WorldStatic, CollisionParams))
			{
				if (HitResult.GetActor() != nullptr)
				{
					FString Name = HitResult.GetActor()->GetName();
					UE_LOG(LogTemp, Warning, TEXT("HitResult.GetActor() is not nullptr:%s"), *Name);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("HitResult.GetActor() is nullptr"));
					return;
				}
				
				// Debug LineTrace
				// FVector Start = HitResult.TraceStart;
				// DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f, 0, 1.0f);
				//
				//
				// FVector HitLocation = HitResult.ImpactPoint;
				// DrawDebugPoint(GetWorld(), HitLocation, 10.0f, FColor::Green, false, 2.0f);
				ASunToken* Sunlight = Cast<ASunToken>(HitResult.GetActor());
				if (Sunlight)
				{
					UGameplayStatics::PlaySound2D(this,SunlightSoundCue);
					Sunlight->AddSunlight(true);
					UE_LOG(LogTemp,Display,TEXT("AddSunlight"))
					return;
				}
			
				APlantPlaceArea* PlantPlaceActor = Cast<APlantPlaceArea>(HitResult.GetActor());
				if (PlantPlaceActor)
				{
					UE_LOG(LogTemp, Warning, TEXT("PlantPlaceActor is not nullptr"));
					if (!PlantPlaceActor->IsOccupied())
					{
						FVector PlacementLocation = PlantPlaceActor->GetPlacementLocation();
						FActorSpawnParameters SpawnParams;
						SpawnParams.bNoFail = true;
						if (CurrentPlantName.IsEmpty())
						{
							UE_LOG(LogTemp, Warning, TEXT("No PlantName provided!"));
							return;
						}
						FName PlantName = FName(*CurrentPlantName);
						FPlantStructureBase* PlantData = PlantDataTable->FindRow<FPlantStructureBase>(PlantName,TEXT("Context String"));
						UClass* PlantClassToSpawn = PlantClassMap[CurrentPlantName];
						APaperZDCharacterBase* NewPlant = GetWorld()->SpawnActor<APaperZDCharacterBase>(PlantClassToSpawn, PlacementLocation, FRotator::ZeroRotator,SpawnParams);
						UE_LOG(LogTemp,Display,TEXT("Spawn Plant:%s"),*NewPlant->GetName())
						if (NewPlant)
						{
							NewPlant->bFollowMouse = false;
							PlantPlaceActor->Occupy(NewPlant);
							if (PlantData->name == FName(TEXT("Jalapeno")))
							{
								PlantPlaceActor->NotOccupy();
							}
							OnMyMouseClickedDelegate.Broadcast(PlantName);
							UGameplayStatics::PlaySound2D(this,PlantSoundCue);
							UE_LOG(LogTemp, Warning, TEXT("Plant Successfully!"));
							CurrentPlantName = nullptr;
						}
						else
						{
							UE_LOG(LogTemp, Warning, TEXT("Plant Failed!"));
						}
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("PlantPlaceActor is Occupied!"));
					}
				}
				}
				
			}
		}
	

	// APVZGameModeBase* GameMode = Cast<APVZGameModeBase>(GetWorld()->GetAuthGameMode());


bool APlantPlayerController::PurchasePlant(const FString& PlantName, int32 PlantCost)
{
	FString CurrentName = GetCurrentPlayerName();
	UPlayerSaveGame* PlayerSaveGame = Cast<UPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot(CurrentName, 0));

	if (!PlayerSaveGame)
	{
		UE_LOG(LogTemp,Warning,TEXT("PlayerSaveGame is nullptr"));
		// Handle the case where the save game does not exist
		return false;
	}
		
	if (PlayerSaveGame->UserGold >= PlantCost)
	{
		
		FName PlantFName = FName(*PlantName); 
		FPlantStructureBase* PlantData = PlantDataTable->FindRow<FPlantStructureBase>(PlantFName, TEXT("Context String"));
		if (PlantData->bUnlocked == true)
		{
			UE_LOG(LogTemp,Display,TEXT("You Have Unlocked This Plant"));
			return false;
		}
		PlayerSaveGame->UserGold -= PlantCost;
		PlayerSaveGame->UnlockedPlants.AddUnique(PlantName);
		// Save the game after purchasing
		UGameplayStatics::SaveGameToSlot(PlayerSaveGame, CurrentName, 0);

		// Update the plant's unlocked status in the DataTable
		UpdatePlantUnlockedStatus(PlantName, true);
	
		// TODO: Update UI and provide feedback to the player -> BluePrint

		return true;
	}
	else
	{
		// TODO: Notify player that they do not have enough gold -> BluePrint
		UE_LOG(LogTemp, Warning, TEXT("do not have enough gold"));
		return false;
	}
}
void APlantPlayerController::UpdatePlantUnlockedStatus(const FString& PlantName, bool NewStatus)
{
	FName PlantFName = FName(*PlantName); 
	FPlantStructureBase* PlantData = PlantDataTable->FindRow<FPlantStructureBase>(PlantFName, TEXT("Context String"));
	if (PlantData)
	{
		PlantData->bUnlocked = true;
	}
}
// void APlantPlayerController::LockAllPlants()
// {
// 	if (PlantDataTable != nullptr)
// 	{
// 		PlantDataTable->ForeachRow<FPlantStructureBase>(TEXT("LockAllPlants"), [this](const FName& RowName, const FPlantStructureBase& RowData)
// 		{
// 			LockPlant(RowName); 
// 		});
// 	}
// }
void APlantPlayerController::LockAllPlants()
{
	if (PlantDataTable!=nullptr)
	{
		PlantDataTable->ForeachRow<FPlantStructureBase>(TEXT("LockedAllPlants"),[this](const FName& RowName,const FPlantStructureBase& RowData)
		{
			FPlantStructureBase* PlantData = PlantDataTable->FindRow<FPlantStructureBase>(RowName,TEXT("Context String"));
			if (PlantData)
			{
				PlantData->bUnlocked = false;
				//UE_LOG(LogTemp,Display,TEXT("Lock Plants:%s"),*RowName.ToString());
			}
		});
	}
}

void APlantPlayerController::SaveSoundSettings(float soundIntensity)
{
	if (UGameplayStatics::DoesSaveGameExist(CurrentPlayerName, 0))
	{
		UPlayerSaveGame* SaveGameInstance = Cast<UPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot(CurrentPlayerName,0));
		if (SaveGameInstance)
		{
			SaveGameInstance->soundIntensity = soundIntensity;
			UGameplayStatics::SaveGameToSlot(SaveGameInstance,CurrentPlayerName,0);
		}
	}
}

void APlantPlayerController::SetCurrentPlayerName(const FString& NewPlayerName)
{
	CurrentPlayerName = NewPlayerName;
}

FString APlantPlayerController::GetCurrentPlayerName() const
{
	return CurrentPlayerName;
}

void APlantPlayerController::UnlockPlant(const FString& PlantName)
{
	UPlayerSaveGame* SaveGameInstance = Cast<UPlayerSaveGame>(UGameplayStatics::CreateSaveGameObject(UPlayerSaveGame::StaticClass()));
	if (UGameplayStatics::DoesSaveGameExist(CurrentPlayerName,0))
	{
		SaveGameInstance = Cast<UPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot(CurrentPlayerName, 0));
	}
	SaveGameInstance->UnlockedPlants.AddUnique(*PlantName);
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, CurrentPlayerName, 0);
}

void APlantPlayerController::LoadGame()
{
	if (UGameplayStatics::DoesSaveGameExist(CurrentPlayerName, 0))
	{
		UPlayerSaveGame* LoadGameInstance = Cast<UPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot(CurrentPlayerName, 0));
		TArray<FString> UnlockedPlants = LoadGameInstance->UnlockedPlants;
		LockAllPlants();
		for (const FString& PlantName:UnlockedPlants)
		{
			UpdatePlantUnlockedStatus(PlantName,true);
			//UE_LOG(LogTemp,Display,TEXT("Update"))
		}
	}
}

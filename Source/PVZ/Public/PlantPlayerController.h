// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PaperTileMapComponent.h"
#include "Plant/PaperZDCharacterBase.h"
#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/PlayerController.h"
#include "User/PlayerSaveGame.h"
#include "PlantPlayerController.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMyMouseClickedDelegate,FName,PlantName);

UCLASS()
class PVZ_API APlantPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void SetupInputComponent() override;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	TSubclassOf<APaperZDCharacterBase> PlantClass;
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintAssignable)
	FOnMyMouseClickedDelegate OnMyMouseClickedDelegate;
	
	void OnMouseClicked();

	UFUNCTION(BlueprintCallable, Category="Economy")
	bool PurchasePlant(const FString& PlantName,int32 PlantCost);

private:
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere,Category = "Setup",meta = (AllowPrivateAccess = true))
	FString CurrentPlayerName = FString("DefaultPlayerSave");
	
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere,Category = "Setup",meta = (AllowPrivateAccess = true))
	bool bStartGame = false;
	
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere,Category = Plant,meta = (AllowPrivateAccess = true))
	FString CurrentPlantName;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = Plant,meta = (AllowPrivateAccess = true))
	USoundBase* PlantSoundCue;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = Plant,meta = (AllowPrivateAccess = true))
	USoundBase* SunlightSoundCue;

public:
	void SetCurrentPlayerName(const FString& NewPlayerName);
	FString GetCurrentPlayerName() const;
	void UnlockPlant(const FString& PlantName);
	void LoadGame();
	void UpdatePlantUnlockedStatus(const FString& PlantName, bool NewStatus);
	void LockAllPlants();
	UFUNCTION(BlueprintCallable,Category = "SaveGame")
	void SaveSoundSettings(float soundIntensity);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plants")
	UDataTable* PlantDataTable;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Plants")
	TMap<FString, TSubclassOf<APaperZDCharacterBase>> PlantClassMap;
};

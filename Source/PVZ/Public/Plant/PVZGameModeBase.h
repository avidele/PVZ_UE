// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacterBase.h"
#include "GameFramework/GameModeBase.h"
#include "User/PlayerSaveGame.h"
#include "PVZGameModeBase.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameWinDelegate, int32, currentLevelNum);
/**
 * 
 */
UCLASS()
class PVZ_API APVZGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	APVZGameModeBase();
	// UFUNCTION(BlueprintCallable, Category = "Character")
	// void Spawn2DCharacter();
	//
	// void DestroyPlant(APaperZDCharacterBase* PlantToDelete);
public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure, Category = "SaveGame")
	UPlayerSaveGame* GetLoadedSaveGame() const;
	UPROPERTY(BlueprintAssignable)
	FGameWinDelegate GameWinDelegate;
private:
	UFUNCTION(BlueprintCallable)
	void OnGameWin(int32 currentLevelNum = 1);

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "GoldNum",meta = (AllowPrivateAccess = true))
	int32 GoldNum = 100;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "PlayerScore",meta = (AllowPrivateAccess = true))
	int32 PlayerScore = 1000;
protected:
	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	// TSubclassOf<APaperZDCharacterBase> PaperZDCharacter;

	//APaperZDCharacterBase* SpawnedCharacter;
};

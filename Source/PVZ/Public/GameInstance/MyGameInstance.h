#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "User/PlayerSaveGame.h"
#include "MyGameInstance.generated.h"

UCLASS()
class PVZ_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	static TArray<FString> GetAllSaveGameSlots();

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	bool LoadSelectedSaveGame(const FString& SelectedSlot);

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void CreateLoad(FString LoadName);
	
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	int32 GetPlayerGold() const;

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	TMap<FString,int> GetPlayerRank() const;
	
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	int32 GetPlayerRankNum() const;

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	float GetPlayerScore() const;

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	int32 GetPlayerLevel() const;
	
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	UPlayerSaveGame* GetSaveGame() const;

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void DeleteGameLoad(FString LoadName);

	UPROPERTY(BlueprintReadWrite,Category = "SaveGame")
	FString CurrentName;
};
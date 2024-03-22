#pragma once
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlayerSaveGame.generated.h"

UCLASS()
class PVZ_API UPlayerSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPlayerSaveGame();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category = Basic)
	FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString PlayerPassword; // Notice todo: This is not safe, should be encrypted

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = Basic)
	int32 UserGold;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	TArray<FString> UnlockedPlants;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = Basic)
	float soundIntensity;
	
	UFUNCTION(BlueprintCallable, Category="Account")
	static UPlayerSaveGame* RegisterNewPlayer(const FString& Username, const FString& Password);

	UFUNCTION(BlueprintCallable, Category="Account")
	static UPlayerSaveGame* LoginPlayer(const FString& Username, const FString& Password);

	UPROPERTY(VisibleAnywhere,Category = Basic,BlueprintReadWrite)
	int32 UnlockedLevelNum = 1;

	UPROPERTY(VisibleAnywhere,Category = Basic,BlueprintReadWrite)
	float PlayerScore = 0.0f;
};
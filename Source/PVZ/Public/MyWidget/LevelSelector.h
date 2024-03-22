// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "LevelSelector.generated.h"

/**
 * 
 */
UCLASS()
class PVZ_API ULevelSelector : public UUserWidget
{
	GENERATED_BODY()
public:
	ULevelSelector(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(meta = (BindWidget),BlueprintReadWrite)
	UButton* Level1;
	UPROPERTY(meta = (BindWidget),BlueprintReadWrite)
	UButton* Level2;
	UPROPERTY(meta = (BindWidget),BlueprintReadWrite)
	UButton* Level3;

	//click button to load level
	UFUNCTION()
	void OnLevel1Clicked();
	UFUNCTION()
	void OnLevel2Clicked();
	UFUNCTION()
	void OnLevel3Clicked();
private:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta = (AllowPrivateAccess = true))
	int32 levelNum;
};

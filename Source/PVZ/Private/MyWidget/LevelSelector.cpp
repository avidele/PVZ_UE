// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWidget/LevelSelector.h"

#include "GameInstance/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

ULevelSelector::ULevelSelector(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Bind button click event
	if (Level1)
	{
		Level1->OnClicked.AddDynamic(this, &ULevelSelector::OnLevel1Clicked);
	}
	if (Level2)
	{
		Level2->OnClicked.AddDynamic(this, &ULevelSelector::OnLevel2Clicked);
	}
	if (Level3)
	{
		Level3->OnClicked.AddDynamic(this, &ULevelSelector::OnLevel3Clicked);
	}
	
}

void ULevelSelector::OnLevel1Clicked()
{
	//Load level
	UGameplayStatics::OpenLevel(this,TEXT("Level1"));
	UE_LOG(LogTemp,Display,TEXT("Leve1 Open"));
}

void ULevelSelector::OnLevel2Clicked()
{
	//Load level
	UGameplayStatics::OpenLevel(this,TEXT("Level2"));
}

void ULevelSelector::OnLevel3Clicked()
{
	//Load level
	UGameplayStatics::OpenLevel(this,TEXT("Level3"));
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Plant/PaperZDCharacterBase.h"
#include "Kismet/GameplayStatics.h"


APaperZDCharacterBase::APaperZDCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APaperZDCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void APaperZDCharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FVector2D MouseScreenPosition;
	UGameplayStatics::GetPlayerController(this, 0)->GetMousePosition(MouseScreenPosition.X, MouseScreenPosition.Y);
	FVector MouseWorldPosition;
	FVector MouseDirection;
	UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(this, 0), MouseScreenPosition, MouseWorldPosition, MouseDirection);
	if (bFollowMouse)
	{
		SetActorLocation(MouseWorldPosition, true);
	}
}

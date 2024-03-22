// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "PaperZDCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class PVZ_API APaperZDCharacterBase : public APaperZDCharacter
{
	GENERATED_BODY()
	APaperZDCharacterBase();
protected:
	virtual void BeginPlay() override;
public:
	
	virtual void Tick(float DeltaSeconds) override;
	bool bFollowMouse = true;
};

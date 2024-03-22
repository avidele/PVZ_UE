#pragma once
#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "ZombieCharacterBase.generated.h"

UCLASS()
class PVZ_API AZombieCharacterBase:public APaperZDCharacter
{
	GENERATED_BODY()	
public:
	AZombieCharacterBase();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Character")
	USkeletalMeshComponent* skeletonMeshComponent;
};



// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor/ZombieSpawner.h"

#include "GameFramework/Character.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Zombie/ZombieAIController.h"

// Sets default values
AZombieSpawner::AZombieSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AZombieSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZombieSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZombieSpawner::SpawnZombie(TSubclassOf<ACharacter> ZombieClass)
{
	if (ZombieClass)
	{
		FActorSpawnParameters SpawnParams;
		FVector SpawnLocation = GetActorLocation();
		SpawnLocation.Y = 10.0f;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		ACharacter* SpawnedCharacter =	GetWorld()->SpawnActor<ACharacter>(ZombieClass, SpawnLocation, GetActorRotation(), SpawnParams);
		AAIController* AIController = GetWorld()->SpawnActor<AAIController>(AZombieAIController::StaticClass());
		if (AIController)
		{
			// Possess the Character with the AIController
			AIController->Possess(SpawnedCharacter);
		}
	}
}


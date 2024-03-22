#include "Zombie/ZombieCharacterBase.h"

AZombieCharacterBase::AZombieCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
}

void AZombieCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AZombieCharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

#include "Sunlight/SunToken.h"

#include "Chaos/ChaosPerfTest.h"

ASunToken::ASunToken()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(SceneComponent);
	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipookComponent"));
	FlipbookComponent->SetupAttachment(SceneComponent);
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
}


bool ASunToken::AddSunlight_Implementation(bool bAdd)
{
	return bAdd;
}

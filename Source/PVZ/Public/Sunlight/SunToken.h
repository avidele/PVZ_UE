#pragma once
#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "SunToken.generated.h"



UCLASS()
class ASunToken:public AActor
{
	GENERATED_BODY()
	ASunToken();
public:
	UPROPERTY(EditAnywhere,Category="Setup")
	USceneComponent* SceneComponent;
	UPROPERTY(EditAnywhere,Category="Setup")
	USphereComponent* SphereComponent;
	UPROPERTY(EditAnywhere,Category="Setup")
	UPaperFlipbookComponent* FlipbookComponent;
	UPROPERTY(EditAnywhere,Category="Setup")
	UProjectileMovementComponent* ProjectileMovementComponent;
	UFUNCTION(BlueprintNativeEvent, Category = "Your Category")
	bool AddSunlight(bool bAdd);
	virtual bool AddSunlight_Implementation(bool bAdd);
// public:
// 	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Setup")
// 	USoundCue* SunlightSound;
};

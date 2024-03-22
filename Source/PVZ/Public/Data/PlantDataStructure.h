#pragma once
#include "PaperZDCharacter.h"
#include "Engine/DataTable.h"
#include "PlantDataStructure.generated.h"
/** Please add a struct description */

USTRUCT(BlueprintType)
struct FPlantStructureBase :public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="name", MakeStructureDefaultValue="None"))
	FName name;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="unlockedImage", MakeStructureDefaultValue="None"))
	TObjectPtr<UTexture2D> unlockedImage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="lockedImage", MakeStructureDefaultValue="None"))
	TObjectPtr<UTexture2D> lockedImage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="cost", MakeStructureDefaultValue="None"))
	float cost = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="bUnlocked", MakeStructureDefaultValue="None"))
	bool bUnlocked = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayNae="bActivated", MakeStructureDefaultValue="None"))
	bool bActivated = false;

	// UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(DisplayName="hasPlantNum",MakeStructureDefaultValue="None"))
	// int32 hasPlantNum = 0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(DisplayName="FrozenTime",MakeStructureDefaultValue="None"))
	float FrozenTime = 0.0f;
};

// class PVZ_API MyPlantDataTableBase:public UDataTable
// {
// public:
// 	MyPlantDataTableBase();
// 	void UpdateUnlockedStatus(const TArray<FString>& UnlockedPlantNames);
// private:
// 	UDataTable* MyPlantDataTable;
// };

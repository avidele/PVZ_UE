// // Fill out your copyright notice in the Description page of Project Settings.
//
//
// #include "MyWidget/AllPlants.h"
//
// #include "Data/PlantDataStructure.h"
// #include "UObject/ConstructorHelpers.h"
// #include "Materials/MaterialInterface.h"
//
// void UAllPlants::InitializeGridPanel()
// {
// 	if (!MyGridPanel||!MaterialDataTable)
// 	{
// 		return;
// 	}
// 	MyGridPanel->ClearChildren();
// 	for (int32 Row = 0; Row<8; ++Row)
// 	{
// 		for (int32 Col = 0;Col <5;++Col)
// 		{
// 			UImage* NewImage = NewObject<UImage>(this,UImage::StaticClass());
// 			if (NewImage)
// 			{
// 				
// 				FName RowName = *FString::Printf(TEXT("%d"),Row*5+Col);
// 				FPlantStructureBase* MaterialData = MaterialDataTable->FindRow<FPlantStructureBase>(RowName,TEXT(""));
// 				if (MaterialData && MaterialData->Image)
// 				{
// 					NewImage->SetBrushFromTexture(MaterialData->Image);
// 					MyGridPanel->AddChildToGrid(NewImage, Row, Col);
// 				}
// 			}
// 		}
// 	}
// }

// // Fill out your copyright notice in the Description page of Project Settings.
//
// #pragma once
//
// #include "CoreMinimal.h"
// #include "Blueprint/UserWidget.h"
// #include "Components/Image.h"
// #include "Engine/DataTable.h"
// #include "Components/GridPanel.h"
// #include "AllPlants.generated.h"
//
// /**
//  * 
//  */
// UCLASS()
// class PVZ_API UAllPlants : public UUserWidget
// {
// 	GENERATED_BODY()
// public:
// 	UPROPERTY(BlueprintReadOnly,meta = (BindWidget))
// 	UGridPanel* MyGridPanel;
//
// 	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "data")
// 	UDataTable* MaterialDataTable;
//
// 	UFUNCTION(BlueprintCallable)
// 	void InitializeGridPanel();
// };

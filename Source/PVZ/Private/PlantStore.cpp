// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantStore.h"

#include "PlantDragDropOperation.h"
#include "PlantPlace.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

FReply UPlantStore::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		UPlantDragDropOperation* DragOperation = NewObject<UPlantDragDropOperation>(this);
		DragOperation->DefaultDragVisual = this;
		DragOperation->Payload = this;
		DragOperation->Pivot = EDragPivot::MouseDown;
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}
	return FReply::Unhandled();
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

FReply UPlantStore::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	//todo ExtraDragged
	return Super::NativeOnMouseMove(InGeometry, InMouseEvent);
}

bool UPlantStore::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	FVector2D ScreenPosition = InDragDropEvent.GetScreenSpacePosition();
	FVector WorldPosition, WorldDirection;
	UWorld* World = GetWorld();
	APlayerController *PlayerController = World->GetFirstPlayerController();
	UGameplayStatics::DeprojectScreenToWorld(PlayerController, ScreenPosition, WorldPosition, WorldDirection);
	FVector PlaneNormal = FVector(0, 0, -1);
	FVector PlaneOrigin = FVector(0, 0, 0);
	FVector HitPoint = FMath::LinePlaneIntersection(WorldPosition, WorldPosition + WorldDirection * 10000.0f, PlaneOrigin, PlaneNormal);
	return true;
}
// 	UPlantDragDropOperation* PlantOperation = Cast<UPlantDragDropOperation>(InOperation);
// 	if (PlantOperation && PlantOperation->DraggedPlant)
// 	{
// 		APlant* DraggedPlant = PlantOperation->DraggedPlant;
//
// 		// 遍历查找最近的植物放置区域
// 		float ClosestDistanceSquared = FLT_MAX;
// 		APlantPlace* ClosestSlot = nullptr;
//         
// 		for (APlantPlace* PlantSlot : PlantSlots)  // 假设 PlantSlots 是你所有植物放置区域的数组
// 			{
// 			if (PlantSlot->CanPlacePlant())
// 			{
// 				float DistanceSquared = FVector::DistSquared(PlantSlot->GetActorLocation(), DraggedPlant->GetActorLocation());
// 				if (DistanceSquared < ClosestDistanceSquared)
// 				{
// 					ClosestDistanceSquared = DistanceSquared;
// 					ClosestSlot = PlantSlot;
// 				}
// 			}
// 			}
//
// 		if (ClosestSlot)
// 		{
// 			// 放置植物
// 			DraggedPlant->SetActorLocation(ClosestSlot->GetActorLocation());
// 			ClosestSlot->OnPlantPlaced();
//
// 			return true;
// 		}
// 	}
//



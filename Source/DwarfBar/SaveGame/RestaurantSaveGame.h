// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DwarfBar/Structure/FTableData.h"
#include "RestaurantSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class DWARFBAR_API URestaurantSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Data)
	TMap<FVector2D,FTableData> TableData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Data)
	TMap<FVector2D, FVector2D> ChairToTable;
};

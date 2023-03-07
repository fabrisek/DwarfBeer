// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FTile.h"
#include "TileStruct.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct FTileStruct
{
	GENERATED_BODY();
public:
	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	TArray<FTile> TilesArray;
};
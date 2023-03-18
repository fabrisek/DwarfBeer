
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefaultObject.h"
#include "PDA_Object.h"
#include "Structure/FObjectTile.h"
#include "FTile.generated.h"

USTRUCT(BlueprintType)
struct FTile
{
	GENERATED_USTRUCT_BODY()

public:
	// Sets default values for this actor's properties
	FTile()
	{
		TilePosition = FVector2D();
		ObjectsInTile = TArray<FObjectTile>();
		AllTileBatiment = TArray<FVector2D>();
	}

	UPROPERTY(EditAnywhere, Category = "Position")
	FVector2D TilePosition;
	
	UPROPERTY(EditAnywhere, Category = "Position")
	TArray<FObjectTile> ObjectsInTile;
	
	UPROPERTY(EditAnywhere, Category = "Position")
	TArray<FVector2D> AllTileBatiment;

	// Serialize the structure
	friend FArchive& operator<<(FArchive& Archive, FTile& Tile)
	{
		Archive << Tile.TilePosition;
		Archive << Tile.ObjectsInTile;
		Archive << Tile.AllTileBatiment;
		
		return Archive;
	}
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefaultObject.h"
#include "PDA_Object.h"
#include "FTile.generated.h"

USTRUCT(BlueprintType)
struct FTile
{
	GENERATED_USTRUCT_BODY()

public:
	// Sets default values for this actor's properties
	FTile()
	{
		IdDataRow = "Cube";
		bIsEmpty = true;
	}
	
	UPROPERTY(EditAnywhere, Category = "Data")
	FName IdDataRow;
	UPROPERTY(EditAnywhere, Category = "Position")
	FVector2D TilePosition;
	UPROPERTY(EditAnywhere, Category = "Position")
	bool bIsEmpty;
	//ADefaultObject* ObjectReference;
	//UPDA_Object* DataObject;
	UPROPERTY(EditAnywhere, Category = "Position")
	TArray<FVector2D> AllTileBatiment;

	// Serialize the structure
	friend FArchive& operator<<(FArchive& Archive, FTile& Tile)
	{
		Archive << Tile.IdDataRow;
		Archive << Tile.bIsEmpty;
		Archive << Tile.AllTileBatiment;
		Archive << Tile.TilePosition;
		
		return Archive;
	}
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FTile.h"
#include "ChunkStruct.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct FChunkStruct
{
FChunkStruct()
{
	ChunkPosition = FVector2D();
	Tiles = TMap<FVector2D,FTile>();
}
	
	GENERATED_BODY();
public:
	UPROPERTY(EditAnywhere)
	FVector2D ChunkPosition;
	UPROPERTY(EditAnywhere)
	TMap<FVector2D,FTile> Tiles;

	// Serialize the structure
	friend FArchive& operator<<(FArchive& Archive, FChunkStruct& Chunk)
	{
		Archive << Chunk.ChunkPosition;
		Archive << Chunk.Tiles;
		return Archive;
	}
};
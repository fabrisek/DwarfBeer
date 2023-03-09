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
	GENERATED_BODY();
public:
	UPROPERTY(EditAnywhere)
	FVector2D ChunkPosition;
	UPROPERTY(EditAnywhere)
	TArray<FTile> TilesArray;

	// Serialize the structure
	friend FArchive& operator<<(FArchive& Archive, FChunkStruct& Chunk)
	{
		Archive << Chunk.ChunkPosition;
		Archive << Chunk.TilesArray;
		return Archive;
	}
};
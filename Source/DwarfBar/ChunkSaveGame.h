// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChunkStruct.h"
#include "GameFramework/SaveGame.h"
#include "ChunkSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class DWARFBAR_API UChunkSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Grid")
	FChunkStruct ChunkData;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/Actor.h"
#include "Chunk.h"
#include "ChunkStruct.h"
#include "ChunkManager.generated.h"

UCLASS()
class DWARFBAR_API AChunkManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChunkManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FTile GetTileAtPosition(FVector2d MousePosition);
	
	bool CheckIfChunkDataExist(FVector2d ChunkPosition);
	FChunkStruct GetChunkData(FVector2d ChunkPosition);
	void SaveGame(FChunkStruct Data, FVector2d ChunkPosition);
	TArray<FVector2D>GetAllTilePositions( FVector2D ReferenceTilePosition, int BuildingWidth, int BuildingHeight, int Rotation);
	UPROPERTY(EditDefaultsOnly, Category = "NeightBoorChunk")
	TArray<FVector2D> NeightBoorChunk;
	UPROPERTY(EditDefaultsOnly, Category = "NeightBoorChunk")
	int RangeNeedToBeLoad;
	UPROPERTY(EditDefaultsOnly, Category = "DATA to Instance")
	TMap<FVector2D, AChunk*> ChargedChunk;

	void ChangeTileData(FTile TileData, FVector2d MouseTilePosition);
	bool CheckIfTileIsEmpty(FVector2d TilePosition, int BuildWidth,int BuildHeight, int Rotation);
	AChunk* GetChunkReference(FVector2d MouseTilePosition);
	TArray<FVector2D> FindAdjcenteTile(FVector2D TilePosition, int hauteurTile, int longueurTile);
	void RemoveObjectAtPosition(FVector2D TilePosition);
	
private:
	FVector2D GetPlayerChunkPosition();
	TArray<FVector2D>GetNeightBoorChunk();
	void GenerateChunk(FVector2D ChunkPosition);
	void ManageChunkLoading();
	TArray<FVector2D> AllPositionChunkLoad;

};

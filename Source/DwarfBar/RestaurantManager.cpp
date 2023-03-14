// Fill out your copyright notice in the Description page of Project Settings.


#include "RestaurantManager.h"
#include "FTile.h"


// Sets default values
ARestaurantManager::ARestaurantManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARestaurantManager::BeginPlay()
{
	Super::BeginPlay();
	
	ChunkManager = Cast<AChunkManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AChunkManager::StaticClass()));
}

// Called every frame
void ARestaurantManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARestaurantManager::AddTable(FVector2D TilePosition)
{
	FTableData Data;
	Data.TilePosition = TilePosition;
	TArray<FVector2D> AdjacentTile = ChunkManager->FindAdjcenteTile(TilePosition,1,1);
	for (int i = 0; i < AdjacentTile.Num(); i++)
	{
		FTile Tile = ChunkManager->GetTileAtPosition(AdjacentTile[i]);
		if (!Tile.bIsEmpty)
		{
			if (Tile.IdDataRow == "Chair")
			{
				if (!ChairToTable.Contains(AdjacentTile[i]))
				{
					Data.ChairPosition.Add(AdjacentTile[i]);
					ChairToTable.Add(AdjacentTile[i], TilePosition);
				}
			}
		}
	}
	TableData.Add(TilePosition,Data);
}

void ARestaurantManager::AddChair(FVector2D TilePosition)
{
	TArray<FVector2D> AdjacentTile = ChunkManager->FindAdjcenteTile(TilePosition,1,1);
	for (int i = 0; i < AdjacentTile.Num(); i++)
	{
		FTile Tile = ChunkManager->GetTileAtPosition(AdjacentTile[i]);
		if (!Tile.bIsEmpty)
		{
			if (Tile.IdDataRow == "Table")
			{
				if (TableData.Contains(AdjacentTile[i]))
				{
					FTableData Data = TableData[AdjacentTile[i]];
					Data.ChairPosition.Add(TilePosition);
					ChairToTable.Add(TilePosition, AdjacentTile[i]);
					TableData[AdjacentTile[i]] = Data;
					return;
				}
			}
		}	
	}
}

void ARestaurantManager::RemoveTable(FVector2D TilePosition)
{
}

void ARestaurantManager::RemoveChair(FVector2D TilePosition)
{
}


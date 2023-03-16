// Fill out your copyright notice in the Description page of Project Settings.


#include "RestaurantManager.h"
#include "FTile.h"
#include "SaveGame/RestaurantSaveGame.h"


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
	CheckIfSaveExist();
}

void ARestaurantManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	SaveGame();
}

// Called every frame
void ARestaurantManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckIfNeedCustomers();
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
	TableData.Remove(TilePosition);
}

void ARestaurantManager::RemoveChair(FVector2D TilePosition)
{
	if (TableData.Contains(ChairToTable[TilePosition]))
		TableData[ChairToTable[TilePosition]].ChairPosition.Remove(TilePosition),
	ChairToTable.Remove(TilePosition);
}

void ARestaurantManager::AddDoor(FVector2D TilePosition)
{
	DoorPosition.Add(TilePosition);
}

void ARestaurantManager::RemoveDoor(FVector2D TilePosition)
{
	DoorPosition.Remove(TilePosition);
}

void ARestaurantManager::OpenRestaurant()
{
	bRestaurantIsOpen = true;
}

void ARestaurantManager::CloseRestaurant()
{
	bRestaurantIsOpen = false;
}

void ARestaurantManager::KickCustomers()
{
	
}

void ARestaurantManager::CheckIfNeedCustomers()
{
	if (bRestaurantIsOpen)
	{
		const FTableData FreeTableData = GetFreeTable(1);
		
		if (FreeTableData.TilePosition.X != INT_MAX  )
		{
			const int MaxChair = FreeTableData.ChairPosition.Num();
			int rand = FMath::RandRange(1, MaxChair);
			if(AllNpc.Num() + rand <= ChairToTable.Num() && GroupCustomers.Num() < TableData.Num())
				SpawnCustomers(rand);
		}
	}
}

void ARestaurantManager::SpawnCustomers_Implementation(int Amount)
{
	
}

void ARestaurantManager::AddCustomer(ANpcCharacter* NpcRef)
{
	if (NpcRef != nullptr)
		AllNpc.Add(NpcRef);
}

FTableData ARestaurantManager::GetFreeTable(int CustomerCount)
{
	for (const TPair<FVector2D, FTableData>& pair : TableData)
	{
		if (!pair.Value.bBusyTable && pair.Value.ChairPosition.Num() > 0 && pair.Value.ChairPosition.Num() >= CustomerCount)
			return pair.Value;
	}
	FTableData NullData;
	return NullData;
}

int ARestaurantManager::AddGroup(FGroupCustomers NewGroupCustomers)
{
	return GroupCustomers.Add(NewGroupCustomers);
}

FGroupCustomers ARestaurantManager::GetGroupCustomers(int Index)
{
	if (Index <  GroupCustomers.Num())
		return GroupCustomers[Index];
	else
	{
		FGroupCustomers NullGroup;
		return NullGroup;
	}
}

void ARestaurantManager::SaveGame()
{
	const FString ChunkSaveName = "RestaurantSave";
	USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(ChunkSaveName, 0);
	URestaurantSaveGame* SaveGameObject = Cast<URestaurantSaveGame>(LoadedGame);
	SaveGameObject->ChairToTable = ChairToTable;
	SaveGameObject->TableData = TableData;
	SaveGameObject->DoorPosition = DoorPosition;
	SaveGameObject->bRestaurantIsOpen = bRestaurantIsOpen;
	if (SaveGameObject != nullptr)
		UGameplayStatics::SaveGameToSlot(SaveGameObject, ChunkSaveName, 0);
	
}

void ARestaurantManager::CheckIfSaveExist()
{
	const FString ChunkSaveName = "RestaurantSave";
	USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(ChunkSaveName, 0);
	URestaurantSaveGame* SaveGameObject = Cast<URestaurantSaveGame>(LoadedGame);
	if (!SaveGameObject)
	{
		SaveGameObject = Cast<URestaurantSaveGame>(UGameplayStatics::CreateSaveGameObject(URestaurantSaveGame::StaticClass()));
		UGameplayStatics::SaveGameToSlot(SaveGameObject, ChunkSaveName, 0);
	}
	else
	{
		TableData = SaveGameObject->TableData;
		ChairToTable = SaveGameObject->ChairToTable;
		DoorPosition = SaveGameObject->DoorPosition;
		bRestaurantIsOpen = SaveGameObject->bRestaurantIsOpen;
	}
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AChunkManager::AChunkManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChunkManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AChunkManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ManageChunkLoading();
}

FTile AChunkManager::GetTileAtPosition( FVector2d MousePosition)
{
	// Calcul des coordonnées du chunk correspondant à la position de la souris
	FVector2d ChunkPosition;
	ChunkPosition.X = FMath::FloorToInt(MousePosition.X / 16);
	ChunkPosition.Y = FMath::FloorToInt(MousePosition.Y / 16);

	// Récupération de la référence vers le chunk correspondant
	const AChunk* ChunkRef = ChargedChunk[ChunkPosition];

	// Calcul de l'index de la tuile correspondant à la position de la souris dans le tableau de tuiles du chunk
	const int TileX = FMath::FloorToInt(MousePosition.X) - (ChunkPosition.X * 16);
	const int TileY = FMath::FloorToInt(MousePosition.Y) - (ChunkPosition.Y * 16);
	const int TileIndex = TileX + (TileY * 16);

	// Vérification si l'index est valide
	if (TileIndex >= 0 && TileIndex < 256)
	{
		return ChargedChunk[ChunkPosition]->ChunkData.TilesArray[TileIndex];
	}
	FTile tile;
	return tile;
}

void AChunkManager::ChangeTileData(FTile TileData, FVector2d MouseTilePosition)
{
	// Calcul des coordonnées du chunk correspondant à la position de la souris
	FVector2d ChunkPosition;
	ChunkPosition.X = FMath::FloorToInt(MouseTilePosition.X / 16);
	ChunkPosition.Y = FMath::FloorToInt(MouseTilePosition.Y / 16);

	// Récupération de la référence vers le chunk correspondant
	const AChunk* ChunkRef = ChargedChunk[ChunkPosition];

	// Calcul de l'index de la tuile correspondant à la position de la souris dans le tableau de tuiles du chunk
	const int TileX = FMath::FloorToInt(MouseTilePosition.X) - (ChunkPosition.X * 16);
	const int TileY = FMath::FloorToInt(MouseTilePosition.Y) - (ChunkPosition.Y * 16);
	const int TileIndex = TileX + (TileY * 16);

	// Vérification si l'index est valide
	if (TileIndex >= 0 && TileIndex < 256)
	{
		ChargedChunk[ChunkPosition]->ChunkData.TilesArray[TileIndex] = TileData;
	}
}

bool AChunkManager::CheckIfTileIsEmpty(FVector2d MouseTilePosition)
{
		return GetTileAtPosition(MouseTilePosition).bIsEmpty;
}

AChunk* AChunkManager::GetChunkReference(FVector2d MouseTilePosition)
{
	const FVector2d ChunkPosition = MouseTilePosition / 16;
	return ChargedChunk[ChunkPosition];
}


FVector2D AChunkManager::GetPlayerChunkPosition()
{
	FVector2D ChunkPosition;
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (PlayerPawn != nullptr)
	{
		FVector PlayerPosition = PlayerPawn->GetActorLocation();
		PlayerPosition = PlayerPosition ;
		ChunkPosition.X = FMath::Floor(PlayerPosition.X / 1600);
		ChunkPosition.Y = FMath::Floor(PlayerPosition.Y / 1600);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Impossible de trouver le joueur controle"));
	}
	return ChunkPosition;
}

TArray<FVector2D> AChunkManager::GetNeightBoorChunk()
{
	TArray<FVector2D> ProximityChunk;
	const FVector2D ChunkPosition = GetPlayerChunkPosition();
	for (int X = -RangeNeedToBeLoad; X < RangeNeedToBeLoad; X++)
	{
		for (int Y = -RangeNeedToBeLoad; Y < RangeNeedToBeLoad; Y++)
		{
			ProximityChunk.Add(FVector2D(X + ChunkPosition.X, Y + ChunkPosition.Y));
		}
	}
	return ProximityChunk;
}

void AChunkManager::GenerateChunk(FVector2D ChunkPosition)
{
	AChunk* Chunk = GetWorld()->SpawnActor<AChunk>(AChunk::StaticClass(), FVector(ChunkPosition.X * 16 * 100 , ChunkPosition.Y * 16 * 100, 0.0f), FRotator());
	Chunk->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	AllPositionChunkLoad.Add(ChunkPosition);
	ChargedChunk.Add(ChunkPosition,Chunk);

	if (CheckIfChunkDataExist(ChunkPosition))
	{
		Chunk->GenerateChunk(GetChunkData(ChunkPosition));
		UE_LOG(LogTemp, Warning, TEXT("DATA EXISTE: "));
	}
	else
	{
		Chunk->GenerateChunk(GetChunkData(ChunkPosition));
		UE_LOG(LogTemp, Warning, TEXT("DATA PAS EXIST: "));
	}
}

void AChunkManager::ManageChunkLoading()
{
	NeightBoorChunk = GetNeightBoorChunk();
	for (int i = 0; i < NeightBoorChunk.Num(); i++)
	{
		bool bFind = false;
		AChunk** Chunk = ChargedChunk.Find(NeightBoorChunk[i]);
		if (Chunk != nullptr)
		{
			bFind = true;
		}

		if (!bFind)
		{
			GenerateChunk(NeightBoorChunk[i]);
		}
	}
	TArray<FVector2D> ChunkNeedToBeUnload ;
	for (int j = 0; j < AllPositionChunkLoad.Num(); j++)
	{
		bool bFind = false;
		for (int k = 0; k < NeightBoorChunk.Num(); k++)
		{
			if (AllPositionChunkLoad[j] == NeightBoorChunk[k])
				bFind = true;
		}
		if (bFind == false)
		{
			ChunkNeedToBeUnload.Add(AllPositionChunkLoad[j]);
		}
	}

	for (size_t i = 0; i < ChunkNeedToBeUnload.Num(); i++)
	{
		AChunk** Chunk = ChargedChunk.Find(ChunkNeedToBeUnload[i]);
		if (Chunk != nullptr)
			if ((*Chunk) != nullptr)
			{
				SaveGame((*Chunk)->ChunkData, ChunkNeedToBeUnload[i]);
				(*Chunk)->UnloadChunk();
				ChargedChunk.Remove(ChunkNeedToBeUnload[i]);
				AllPositionChunkLoad.Remove(ChunkNeedToBeUnload[i]);
			}
	}
}

bool AChunkManager::CheckIfChunkDataExist(FVector2d ChunkPosition)
{
	const FString ChunkSaveName = ChunkPosition.ToString();
	USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(ChunkSaveName, 0);
	SaveGameObject = Cast<UChunkSaveGame>(LoadedGame);
	if (!SaveGameObject)
	{
		SaveGameObject = Cast<UChunkSaveGame>(UGameplayStatics::CreateSaveGameObject(UChunkSaveGame::StaticClass()));
		SaveGameObject->ChunkData.ChunkPosition = ChunkPosition;
		UGameplayStatics::SaveGameToSlot(SaveGameObject, ChunkSaveName, 0);
		return false;
	}
		return true;
}

FChunkStruct AChunkManager::GetChunkData(FVector2d ChunkPosition)
{
	const FString ChunkSaveName = ChunkPosition.ToString();
	USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(ChunkSaveName, 0);
	SaveGameObject = Cast<UChunkSaveGame>(LoadedGame);

	return SaveGameObject->ChunkData;
}

void AChunkManager::SaveGame(FChunkStruct Data, FVector2d ChunkPosition)
{
	const FString ChunkSaveName = ChunkPosition.ToString();
	USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(ChunkSaveName, 0);
	SaveGameObject = Cast<UChunkSaveGame>(LoadedGame);
	SaveGameObject->ChunkData = Data;
	
	UGameplayStatics::SaveGameToSlot(SaveGameObject, ChunkSaveName, 0);
}

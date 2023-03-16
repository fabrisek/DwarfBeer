// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkManager.h"

#include "RestaurantManager.h"
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

TArray<FVector2D> AChunkManager::GetAllTilePositions(FVector2D ReferenceTilePosition, int BuildingWidth, int BuildingHeight, int Rotation)
{
    TArray<FVector2D> AllTilePositions;

    // Coordonnées des positions adjacentes par rapport à la position de référence
    FVector2D UpOffset(0, -1);
    FVector2D RightOffset(1, 0);
    FVector2D DownOffset(0, 1);
    FVector2D LeftOffset(-1, 0);

    // Applique la rotation aux positions adjacentes en fonction de la valeur de Rotation
    switch (Rotation)
    {
    case 1: // 90 degrés dans le sens horaire
        UpOffset = FVector2D(-UpOffset.Y, UpOffset.X);
        RightOffset = FVector2D(-RightOffset.Y, RightOffset.X);
        DownOffset = FVector2D(-DownOffset.Y, DownOffset.X);
        LeftOffset = FVector2D(-LeftOffset.Y, LeftOffset.X);
        break;
    case 2: // 180 degrés
        UpOffset *= -1;
        RightOffset *= -1;
        DownOffset *= -1;
        LeftOffset *= -1;
        break;
    case 3: // 90 degrés dans le sens antihoraire
        UpOffset = FVector2D(UpOffset.Y, -UpOffset.X);
        RightOffset = FVector2D(RightOffset.Y, -RightOffset.X);
        DownOffset = FVector2D(DownOffset.Y, -DownOffset.X);
        LeftOffset = FVector2D(LeftOffset.Y, -LeftOffset.X);
        break;
    default: // Rotation de 0 degrés, ne fait rien
        break;
    }

    // Ajoute la position de référence à la liste des positions
    AllTilePositions.Add(ReferenceTilePosition);

    // Boucle sur toutes les lignes et toutes les colonnes de tiles pour calculer les positions
    for (int i = 0; i < BuildingHeight; ++i)
    {
        for (int j = 0; j < BuildingWidth; ++j)
        {
            if (i == 0 && j == 0) continue; // évite de rajouter la position de référence une seconde fois

            // Calcule la position de la tile à partir de la position de référence et des offsets
            const FVector2D TilePosition = ReferenceTilePosition + UpOffset * i + RightOffset * j;
            AllTilePositions.Add(TilePosition);
        }
    }

    return AllTilePositions;
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

bool AChunkManager::CheckIfTileIsEmpty(FVector2d MouseTilePosition, int BuildWidth,int BuildHeight, int Rotation)
{
	TArray<FVector2D> AllTile = GetAllTilePositions(MouseTilePosition, BuildWidth,BuildHeight,Rotation);
	for (int i = 0; i< AllTile.Num(); i++)
	{
		if (!GetTileAtPosition(AllTile[i]).bIsEmpty)
			return false;
	}
	return true;
}

AChunk* AChunkManager::GetChunkReference(FVector2d MouseTilePosition)
{
	const FVector2d ChunkPosition = MouseTilePosition / 16;
	return ChargedChunk[ChunkPosition];
}

TArray<FVector2D> AChunkManager::FindAdjcenteTile(FVector2D TilePosition, int hauteurTile, int longueurTile) 
{
	TArray<FVector2D> casesAdjacentes;

	for (int i = 1; i <= hauteurTile; i++) 
	{
		casesAdjacentes.Add(FVector2D(TilePosition.X + i, TilePosition.Y));    // Case à droite
		casesAdjacentes.Add(FVector2D(TilePosition.X - i, TilePosition.Y));    // Case à gauche
	}

	for (int j = 1; j <= longueurTile; j++) 
	{
		casesAdjacentes.Add(FVector2D(TilePosition.X, TilePosition.Y + j));    // Case en haut
		casesAdjacentes.Add(FVector2D(TilePosition.X, TilePosition.Y - j));    // Case en bas
	}

	return casesAdjacentes;
}

void AChunkManager::RemoveObjectAtPosition(FVector2D TilePosition)
{
	FTile TilePositionRef = GetTileAtPosition(TilePosition);
	if (!TilePositionRef.bIsEmpty)
	{
		for (int i = 0; i < TilePositionRef.AllTileBatiment.Num(); i++)
		{
			FTile TileRef = GetTileAtPosition(TilePositionRef.AllTileBatiment[i]);
			TileRef.bIsEmpty = true;
			TileRef.AllTileBatiment.Empty();
			TileRef.IdDataRow = "None";
			TileRef.ObjectReference = nullptr;
			ChangeTileData(TileRef, TilePositionRef.AllTileBatiment[i]);
		}
		ARestaurantManager* RestaurantManager = Cast<ARestaurantManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ARestaurantManager::StaticClass()));
		switch (TilePositionRef.ObjectReference->TypeObject)
		{
			case EObjectType::Door: 
				RestaurantManager->RemoveDoor(TilePosition);
				break;
			
			case EObjectType::Table:
				RestaurantManager->RemoveTable(TilePosition);
				break;
			
			case EObjectType::Chair:
				RestaurantManager->RemoveChair(TilePosition);

			
			default:
				break;
		}
		TilePositionRef.ObjectReference->Destroy();
	}
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
	for (int X = -(RangeNeedToBeLoad); X < RangeNeedToBeLoad +1 ; X++)
	{
		for (int Y = -(RangeNeedToBeLoad ); Y < RangeNeedToBeLoad+1; Y++)
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
		Chunk->GenerateChunk(GetChunkData(ChunkPosition),true);
		UE_LOG(LogTemp, Warning, TEXT("DATA EXISTE: "));
	}
	else
	{
		Chunk->GenerateChunk(GetChunkData(ChunkPosition),false);
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
// Verifie si la Save existe sinon la creer.
bool AChunkManager::CheckIfChunkDataExist(FVector2d ChunkPosition)
{
	const FString ChunkSaveName = ChunkPosition.ToString();
	USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(ChunkSaveName, 0);
	UChunkSaveGame* SaveGameObject = Cast<UChunkSaveGame>(LoadedGame);
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
	UChunkSaveGame* SaveGameObject = Cast<UChunkSaveGame>(LoadedGame);
	UE_LOG(LogTemp, Warning, TEXT("Valeur de la save : %d"), SaveGameObject->ChunkData.TilesArray.Num());
	UE_LOG(LogTemp, Warning, TEXT("Valeur du ChunkPosition : X = %f, Y = %f"), SaveGameObject->ChunkData.ChunkPosition.X, SaveGameObject->ChunkData.ChunkPosition.Y);
	return SaveGameObject->ChunkData;
}

void AChunkManager::SaveGame(FChunkStruct Data, FVector2d ChunkPosition)
{
	if (Data.TilesArray.Num() > 0)
	{
		
	UE_LOG(LogTemp, Warning, TEXT("Valeur de l'en sauvegarde : %d"), Data.TilesArray.Num());
	const FString ChunkSaveName = ChunkPosition.ToString();
	USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(ChunkSaveName, 0);
	UChunkSaveGame* SaveGameObject = Cast<UChunkSaveGame>(LoadedGame);
		if (SaveGameObject != nullptr)
		{
			SaveGameObject->ChunkData.TilesArray.Empty();
			SaveGameObject->ChunkData = Data;

			UGameplayStatics::SaveGameToSlot(SaveGameObject, ChunkSaveName, 0);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ERREUR PTR"), Data.TilesArray.Num());
		}
	}
}

void AChunkManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

	for(int i = 0 ; i < AllPositionChunkLoad.Num(); i++)
	{
		AChunk** Chunk = ChargedChunk.Find(AllPositionChunkLoad[i]);
		if (Chunk != nullptr)
			if ((*Chunk) != nullptr)
			{
				SaveGame((*Chunk)->ChunkData, AllPositionChunkLoad[i]);
			}		
	}
	Super::EndPlay(EndPlayReason);
}

// Fill out your copyright notice in the Description page of Project Settings.
#include "Chunk.h"
#include <Microsoft/COMPointer.h>
#include "Engine/World.h"
#include "ChunkManager.h"
#include "DwarfGameInstance.h"


// Sets default values
AChunk::AChunk()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	MeshComp = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Mesh"));
}


// Called when the game starts or when spawned
void AChunk::BeginPlay()
{
	Super::BeginPlay();
	const UDwarfGameInstance* MyGameInstance = Cast<UDwarfGameInstance>(GetGameInstance());
	DataTable = MyGameInstance->DataTable;

	
}

// Called every frame
void AChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//Genere le mesh du Chunk
void AChunk::GenerateChunk(FChunkStruct Data, bool bDataExist)
{
	ChunkData = Data;
	FObjectDataTable* Row;
	//Pour les DATA du Chunk
	int Index = 0;

	for (const TPair<FVector2D, FTile>& pair : ChunkData.Tiles)
	{
		FTile Tile = pair.Value;
		for (int i = 0; i < Tile.ObjectsInTile.Num(); i++)
		{
			Row = DataTable->FindRow<FObjectDataTable>(Tile.ObjectsInTile[i].ObjectDataName , TEXT("Cube"));
			if (!Row)
			{
				UE_LOG(LogTemp, Error, TEXT("Row not found"));
				return;
			}
			ADefaultObject* ConstructionObjectInHand = GetWorld()->SpawnActor<ADefaultObject>(ADefaultObject::StaticClass(), FVector(), FRotator::ZeroRotator);

			ConstructionObjectInHand->MeshComp->SetStaticMesh(Row->DataObjectRef->MeshComponent);
			ConstructionObjectInHand->SetActorEnableCollision(true);
			ConstructionObjectInHand->MeshComp->SetMaterial(0,Row->DataObjectRef->Material);

			FVector(pair.Value.TilePosition.X * DistanceCube + 50, pair.Value.TilePosition.Y * DistanceCube + 50, 0.0f);

			FObjectTile TileObject = pair.Value.ObjectsInTile[i];
			TileObject.ObjectReference = ConstructionObjectInHand;
			ConstructionObjectInHand->TilePosition = pair.Value.TilePosition;
			ConstructionObjectInHand->TypeObject = Row->DataObjectRef->ObjectType;
			ConstructionObjectInHand->Rotation = TileObject.Rotation;
			Tile.ObjectsInTile[i] = TileObject;

			if (Row->DataObjectRef->ObjectType == EObjectType::Door || Row->DataObjectRef->ObjectType == EObjectType::Wall)
			{
				switch (TileObject.Rotation)
				{
				case 0:
					ConstructionObjectInHand->SetActorRotation(FRotator(0,0,0));
					ConstructionObjectInHand->SetActorLocation(FVector(pair.Value.TilePosition.X *100, pair.Value.TilePosition.Y*100+50 , 0));
					break;
				case 1:
					ConstructionObjectInHand->SetActorRotation(FRotator(0,90,0));
					ConstructionObjectInHand->SetActorLocation(FVector(pair.Value.TilePosition.X *100+50, pair.Value.TilePosition.Y*100 , 0));
					break;
				case 2:
					ConstructionObjectInHand->SetActorRotation(FRotator(0,180,0));
					ConstructionObjectInHand->SetActorLocation(FVector(pair.Value.TilePosition.X *100, pair.Value.TilePosition.Y*100+50 , 0));
					break;
				case 3:
					ConstructionObjectInHand->SetActorRotation(FRotator(0,270,0));
					ConstructionObjectInHand->SetActorLocation(FVector(pair.Value.TilePosition.X *100+50, pair.Value.TilePosition.Y*100 , 0));
					break;
				default:
					ConstructionObjectInHand->SetActorRotation(FRotator(0,0,0));
					ConstructionObjectInHand->SetActorLocation(FVector(pair.Value.TilePosition.X *100, pair.Value.TilePosition.Y*100+50 , 0));
					break;
				}
			}
			else
			{
				ConstructionObjectInHand->SetActorLocation(FVector(pair.Value.TilePosition.X*100 +50, pair.Value.TilePosition.Y*100 +50, 0));
			
				switch (TileObject.Rotation)
				{
				case 0:
					ConstructionObjectInHand->SetActorRotation(FRotator(0,0,0));
					break;
				case 1:
					ConstructionObjectInHand->SetActorRotation(FRotator(0,90,0));
					break;
				case 2:
					ConstructionObjectInHand->SetActorRotation(FRotator(0,180,0));
					break;
				case 3:
					ConstructionObjectInHand->SetActorRotation(FRotator(0,270,0));
					break;
				default:
					ConstructionObjectInHand->SetActorRotation(FRotator(0,0,0));
					break;
				}
			}
		}
		ChunkData.Tiles[pair.Key] = Tile;
			
	}
	TracerLignesDebogage();
}

void AChunk::UnloadChunk()
{
	Destroy();
}

void AChunk::TracerLignesDebogage()
{
	FVector ChunkPosition = FVector(ChunkData.ChunkPosition.X * 16 * DistanceCube, ChunkData.ChunkPosition.Y * 16 * DistanceCube, 0);

	for (int i = 0; i <= SizeChunk; i++)
	{
		FVector Start = FVector(ChunkPosition.X + (i * DistanceCube), ChunkPosition.Y, ChunkPosition.Z);
		FVector End = FVector(ChunkPosition.X + (i * DistanceCube), ChunkPosition.Y + (SizeChunk * DistanceCube), ChunkPosition.Z);

		DrawDebugLine(GetWorld(), Start, End, FColor::Green, true, -1, 0, 5);
	}

	for (int j = 0; j <= SizeChunk; j++)
	{
		FVector Start = FVector(ChunkPosition.X, ChunkPosition.Y + (j * DistanceCube), ChunkPosition.Z);
		FVector End = FVector(ChunkPosition.X + (SizeChunk * DistanceCube), ChunkPosition.Y + (j * DistanceCube), ChunkPosition.Z);

		DrawDebugLine(GetWorld(), Start, End, FColor::Green, true, -1, 0, 5);
	}
}
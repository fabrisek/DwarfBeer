// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/World.h"
#include "Chunk.h"
#include <Microsoft/COMPointer.h>
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
	TracerLignesDebogage();	
	
}

// Called every frame
void AChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//Genere le mesh du Chunk
void AChunk::GenerateChunk(FChunkStruct Data, bool bDataExist)
{
	FObjectDataTable* Row;

	//Pour les DATA du Chunk
	ChunkData = Data;
	int Index = 0;
	// Boucle pour parcourir les carrés du chunk
	for (int32 X = 0; X < SizeChunk; X++)
	{
		for (int32 Y = 0; Y < SizeChunk; Y++)
		{
			Index++;
			FVector2D TilePosition;
			
			TilePosition.X = (ChunkData.ChunkPosition.X * 16) + Y;
			TilePosition.Y = (ChunkData.ChunkPosition.Y * 16) + X;
			if (!bDataExist)
			{
				// Creation des DATA.

				FTile TiLes;
				TiLes.TilePosition = TilePosition;
				TiLes.bIsEmpty = true;
				ChunkData.TilesArray.Add(TiLes);
			}
			else
			{
				if (!ChunkData.TilesArray[Index -1].bIsEmpty)
				{
					if (ChunkData.TilesArray[Index-1].AllTileBatiment[0] == TilePosition)
					{
						Row = DataTable->FindRow<FObjectDataTable>(ChunkData.TilesArray[Index-1].IdDataRow , TEXT("Cube"));

						if (!Row)
						{
							UE_LOG(LogTemp, Error, TEXT("Row not found"));
							return;
						}

						ADefaultObject* ConstructionObjectInHand = GetWorld()->SpawnActor<ADefaultObject>(ADefaultObject::StaticClass(), FVector(TilePosition.X * DistanceCube , TilePosition.Y * DistanceCube , 0.0f), FRotator::ZeroRotator);

						ConstructionObjectInHand->MeshComp->SetStaticMesh(Row->DataObjectRef->MeshComponent);
						ConstructionObjectInHand->SetActorEnableCollision(true);
						ConstructionObjectInHand->MeshComp->SetMaterial(0,Row->DataObjectRef->Material);

						FTile Tile = ChunkData.TilesArray[Index -1];
						Tile.ObjectReference = ConstructionObjectInHand;
						ChunkData.TilesArray[Index -1] = Tile;

						ConstructionObjectInHand->TilePosition = ChunkData.TilesArray[Index-1].TilePosition;
						ConstructionObjectInHand->TypeObject = Row->DataObjectRef->ObjectType;
						switch (Tile.Rotation)
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
			}
		}
	
	}
}

void AChunk::UnloadChunk()
{
	Destroy();
}

void AChunk::TracerLignesDebogage()
{
	FVector2D ChunkStart = FVector2D(ChunkData.ChunkPosition.X * SizeChunk, ChunkData.ChunkPosition.Y * SizeChunk);
	FVector2D ChunkEnd = ChunkStart + FVector2D(SizeChunk, SizeChunk);

	for (float X = ChunkStart.X; X <= ChunkEnd.X; X++)
	{
		FVector Start = FVector(X * DistanceCube, ChunkStart.Y * DistanceCube, 0.0f);
		FVector End = FVector(X * DistanceCube, ChunkEnd.Y * DistanceCube, 0.0f);
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, true, -1, 0, 1);
	}

	for (float Y = ChunkStart.Y; Y <= ChunkEnd.Y; Y++)
	{
		FVector Start = FVector(ChunkStart.X * DistanceCube, Y * DistanceCube, 0.0f);
		FVector End = FVector(ChunkEnd.X * DistanceCube, Y * DistanceCube, 0.0f);
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, true, -1, 0, 1);
	}
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "Chunk.h"
#include <Microsoft/COMPointer.h>

#include "ChunkManager.h"
#include "Engine/DataTable.h"
#include "Structure/FObjectDataTable.h"


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
}

// Called every frame
void AChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//Genere le mesh du Chunk
void AChunk::GenerateChunk(FChunkStruct Data, bool bDataExist)
{
	TArray<FVector> MeshPositions;
	TArray<FVector> MeshNormals;
	TArray<int32> MeshIndices;

	//Pour les DATA du Chunk
	ChunkData = Data;
	int Index = 0;
	// Boucle pour parcourir les carrés du chunk
	for (int32 X = 0; X < SizeChunk; X++)
	{
		for (int32 Y = 0; Y < SizeChunk; Y++)
		{
			Index++;
			// Calcul des positions des sommets pour chaque carré
			FVector UpperLeftCorner = FVector(X * DistanceCube, Y * DistanceCube, 0.0f);
			FVector LowerRightCorner = FVector((X + 1) * DistanceCube, (Y + 1) * DistanceCube, 0.0f);
			FVector UpperRightCorner = FVector((X + 1) * DistanceCube, Y * DistanceCube, 0.0f);
			FVector LowerLeftCorner = FVector(X * DistanceCube, (Y + 1) * DistanceCube, 0.0f);


			// Ajout des sommets dans le tableau de positions du mesh
			MeshPositions.Add(UpperLeftCorner);
			MeshPositions.Add(LowerRightCorner);
			MeshPositions.Add(LowerLeftCorner);
			MeshPositions.Add(UpperRightCorner);

			// Calcul de la normale de chaque face du carré
			FVector FaceNormal = FVector::CrossProduct((LowerLeftCorner - UpperLeftCorner),
			                                           (UpperRightCorner - UpperLeftCorner)).GetSafeNormal();
			MeshNormals.Add(FaceNormal);
			MeshNormals.Add(FaceNormal);
			MeshNormals.Add(FaceNormal);
			MeshNormals.Add(FaceNormal);

			// Ajout des indices de chaque triangle dans le tableau d'indices du mesh
			int32 UpperLeftIndex = X * SizeChunk * 4 + Y * 4;
			int32 UpperRightIndex = UpperLeftIndex + 3;
			int32 LowerLeftIndex = UpperLeftIndex + 2;
			int32 LowerRightIndex = UpperLeftIndex + 1;
			MeshIndices.Add(UpperLeftIndex);
			MeshIndices.Add(LowerRightIndex);
			MeshIndices.Add(LowerLeftIndex);
			MeshIndices.Add(UpperLeftIndex);
			MeshIndices.Add(UpperRightIndex);
			MeshIndices.Add(LowerRightIndex);

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
				if (ChunkData.TilesArray[Index-1].AllTileBatiment.Num() > 0)
				{
					UE_LOG(LogTemp, Warning, TEXT("Valeur position dans le dans chunk : X = %f, Y = %f"), TilePosition.X, TilePosition.Y);
					UE_LOG(LogTemp, Warning, TEXT("Valeur position dans le dans ARRAY : X = %f, Y = %f"), ChunkData.TilesArray[Index-1].AllTileBatiment[0].X, ChunkData.TilesArray[Index-1].AllTileBatiment[0].Y);
					UE_LOG(LogTemp, Warning, TEXT("Valeur de diu nombre de case prise : %d"), ChunkData.TilesArray[Index-1].AllTileBatiment.Num());

				}
				if (!ChunkData.TilesArray[Index -1].bIsEmpty && ChunkData.TilesArray[Index-1].AllTileBatiment[0] == TilePosition)
				{
					FString DataTablePath = "/Game/DataObject.DataObject";
					UObject* DataTableObject = StaticLoadObject(UDataTable::StaticClass(), nullptr, *DataTablePath);
					
					if (!DataTableObject)
					{
						UE_LOG(LogTemp, Error, TEXT("DataTable not found"));
						return;
					}

					// Vérifie que l'objet chargé est bien un DataTable
					if (UDataTable* DataTable = Cast<UDataTable>(DataTableObject))
					{
						FObjectDataTable* Row = DataTable->FindRow<FObjectDataTable>(TEXT("Cube"), TEXT("Cube"));

						if (!Row)
						{
							UE_LOG(LogTemp, Error, TEXT("Row not found"));
							return;
						}

						ADefaultObject* ConstructionObjectInHand = GetWorld()->SpawnActor<ADefaultObject>(ADefaultObject::StaticClass(), FVector3d(TilePosition.X * DistanceCube,TilePosition.Y * DistanceCube,100) , FRotator());
						ConstructionObjectInHand->MeshComp->SetStaticMesh(Row->DataObjectRef->MeshComponent);
						ConstructionObjectInHand->SetActorEnableCollision(true);
						ConstructionObjectInHand->MeshComp->SetMaterial(0,Row->DataObjectRef->Material);
						MeshComp->SetMaterial(0,Row->DataObjectRef->Material);
					}

					
					//ChunkData.TilesArray[Index].IdData = 
				}	
			}
		}
	}

	// Inversion de la normale en échangeant l'ordre des sommets de chaque triangle
	for (int32 i = 0; i < MeshIndices.Num(); i += 3)
	{
		int32 Temp = MeshIndices[i];
		MeshIndices[i] = MeshIndices[i + 1];
		MeshIndices[i + 1] = Temp;
	}

	MeshComp->CreateMeshSection(0, MeshPositions, MeshIndices, MeshNormals, TArray<FVector2D>(), TArray<FColor>(),
	                            TArray<FProcMeshTangent>(), true);
	
}

void AChunk::UnloadChunk()
{
	Destroy();
}

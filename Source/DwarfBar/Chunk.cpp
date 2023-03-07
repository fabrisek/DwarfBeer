// Fill out your copyright notice in the Description page of Project Settings.


#include "Chunk.h"
#include <Microsoft/COMPointer.h>


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
	InstanceManager = Cast<AMeshInstanceManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AMeshInstanceManager::StaticClass()));
	GenerateChunk();
}

// Called every frame
void AChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AChunk::GenerateChunk()
{
TArray<FVector> MeshPositions;
TArray<FVector> MeshNormals;
TArray<int32> MeshIndices;
const int32 ChunkSizeX = 16;
const int32 ChunkSizeY = 16;
const int32 SquareSize = 100;
// Boucle pour parcourir les carrés du chunk
for (int32 i = 0; i < ChunkSizeX; i++)
{
    for (int32 j = 0; j < ChunkSizeY; j++)
    {
        // Calcul des positions des sommets pour chaque carré
    	FVector UpperLeftCorner = FVector(i * SquareSize, j * SquareSize, 0.0f);
    	FVector LowerRightCorner = FVector((i + 1) * SquareSize, (j + 1) * SquareSize, 0.0f);
    	FVector UpperRightCorner = FVector((i + 1) * SquareSize, j * SquareSize, 0.0f);
    	FVector LowerLeftCorner = FVector(i * SquareSize, (j + 1) * SquareSize, 0.0f);



        // Ajout des sommets dans le tableau de positions du mesh
        MeshPositions.Add(UpperLeftCorner);
        MeshPositions.Add(LowerRightCorner);
        MeshPositions.Add(LowerLeftCorner);
        MeshPositions.Add(UpperRightCorner);

        // Calcul de la normale de chaque face du carré
        FVector FaceNormal = FVector::CrossProduct((LowerLeftCorner - UpperLeftCorner), (UpperRightCorner - UpperLeftCorner)).GetSafeNormal();
        MeshNormals.Add(FaceNormal);
        MeshNormals.Add(FaceNormal);
        MeshNormals.Add(FaceNormal);
        MeshNormals.Add(FaceNormal);

        // Ajout des indices de chaque triangle dans le tableau d'indices du mesh
        int32 UpperLeftIndex = i * ChunkSizeY * 4 + j * 4;
        int32 UpperRightIndex = UpperLeftIndex + 3;
        int32 LowerLeftIndex = UpperLeftIndex + 2;
        int32 LowerRightIndex = UpperLeftIndex + 1;
        MeshIndices.Add(UpperLeftIndex);
        MeshIndices.Add(LowerRightIndex);
        MeshIndices.Add(LowerLeftIndex);
        MeshIndices.Add(UpperLeftIndex);
        MeshIndices.Add(UpperRightIndex);
        MeshIndices.Add(LowerRightIndex);
    }
}

// Inversion de la normale en échangeant l'ordre des sommets de chaque triangle
for (int32 i = 0; i < MeshIndices.Num(); i += 3)
{
    int32 Temp = MeshIndices[i];
    MeshIndices[i] = MeshIndices[i + 1];
    MeshIndices[i + 1] = Temp;
}

MeshComp->CreateMeshSection(0, MeshPositions, MeshIndices, MeshNormals, TArray<FVector2D>(), TArray<FColor>(), TArray<FProcMeshTangent>(), true);
}

void AChunk::UnloadChunk()
{
	Destroy();
}



// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkManager.h"


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
	FVector2D ChunkPosition = GetPlayerChunkPosition();
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
				(*Chunk)->UnloadChunk();
				ChargedChunk.Remove(ChunkNeedToBeUnload[i]);
				AllPositionChunkLoad.Remove(ChunkNeedToBeUnload[i]);
			}
	}
}

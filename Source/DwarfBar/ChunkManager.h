// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/Actor.h"
#include "Chunk.h"
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "NeightBoorChunk")
	TArray<FVector2D> NeightBoorChunk;
	UPROPERTY(EditDefaultsOnly, Category = "NeightBoorChunk")
	int RangeNeedToBeLoad;
	UPROPERTY(EditDefaultsOnly, Category = "DATA to Instance")
	TMap<FVector2D, AChunk*> ChargedChunk;
private:
	FVector2D GetPlayerChunkPosition();
	TArray<FVector2D>GetNeightBoorChunk();
	void GenerateChunk(FVector2D ChunkPosition);
	void ManageChunkLoading();
	TArray<FVector2D> AllPositionChunkLoad;

};

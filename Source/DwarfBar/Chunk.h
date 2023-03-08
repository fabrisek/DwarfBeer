// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChunkStruct.h"
#include <Kismet/GameplayStatics.h>
#include "MeshInstanceManager.h"
#include "FTile.h"
#include "ProceduralMeshComponent.h"
#include "Chunk.generated.h"
UCLASS()
class DWARFBAR_API AChunk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChunk();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	AMeshInstanceManager* InstanceManager;

	UPROPERTY(EditDefaultsOnly, Category = "Chunk")
	int SizeChunk = 16;
	UPROPERTY(EditDefaultsOnly, Category = "Chunk")
	float DistanceCube = 100.0f;
public:
	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	FChunkStruct ChunkData;
	void GenerateChunk(FChunkStruct Data, bool bDataExist);
	UProceduralMeshComponent* MeshComp;

public:
	void UnloadChunk();
};

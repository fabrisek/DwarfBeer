
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FTile.generated.h"

USTRUCT(BlueprintType)
struct FTile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	FTile()
	: IndexMeshInstance(0), IdData(0), TilePosition(FVector2D::ZeroVector)
	{
	}
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	int IndexMeshInstance;
	UPROPERTY(EditDefaultsOnly, Category = "Data")
	int IdData;
	UPROPERTY(EditDefaultsOnly, Category = "Position")
	FVector2D TilePosition;
	UPROPERTY(EditDefaultsOnly, Category = "Position")
	bool bIsEmpty;
};
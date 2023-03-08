
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefaultObject.h"
#include "PDA_Object.h"
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
	UPROPERTY(EditAnywhere, Category = "Mesh")
	int IndexMeshInstance;
	UPROPERTY(EditAnywhere, Category = "Data")
	int IdData;
	UPROPERTY(EditAnywhere, Category = "Position")
	FVector2D TilePosition;
	UPROPERTY(EditAnywhere, Category = "Position")
	bool bIsEmpty;
	UPROPERTY(EditAnywhere, Category = "Position")
	ADefaultObject* ObjectReference;
	UPROPERTY(EditAnywhere, Category = "Position")
	UPDA_Object* DataObject;
	UPROPERTY(EditAnywhere, Category = "Position")
	TArray<FVector2D> AllTileBatiment;
};
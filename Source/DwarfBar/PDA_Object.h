// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Enum/EObjectType.h"
#include "PDA_Object.generated.h"

/**
 * 
 */
UCLASS()
class DWARFBAR_API UPDA_Object : public UPrimaryDataAsset
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMesh* MeshComponent;
	UPROPERTY(EditDefaultsOnly, Category = "IDENTIFIANT")
	FName IdDataRow;
	UPROPERTY(EditDefaultsOnly, Category = "MATERIAL")
	UMaterialInterface* Material;
	UPROPERTY(EditDefaultsOnly, Category = "SIZEGRID")
	FVector2D SizeGrid;
	UPROPERTY(EditDefaultsOnly, Category = "ObjectType")
	EObjectType ObjectType;

	void FinishConstruction(FVector2D TilePosition);
};

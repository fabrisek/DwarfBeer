// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildSystemComponent.h"
#include "GameFramework/Actor.h"
#include "Structure/FTableData.h"
#include "RestaurantManager.generated.h"

UCLASS()
class DWARFBAR_API ARestaurantManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARestaurantManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Info)
	TMap<FVector2D,FTableData> TableData;

	void AddTable(FVector2D TilePosition);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Info)
	AChunkManager* ChunkManager;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "RestaurantManager.h"

#include "Structure/FTableData.h"

// Sets default values
ARestaurantManager::ARestaurantManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARestaurantManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARestaurantManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARestaurantManager::AddTable(FVector2D TilePosition)
{
	FTableData Data;
	Data.TilePosition = TilePosition;
	TableData.Add(TilePosition,Data);
}


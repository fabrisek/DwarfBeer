// Fill out your copyright notice in the Description page of Project Settings.


#include "PDA_Object.h"

#include "RestaurantManager.h"
#include "Kismet/GameplayStatics.h"

void UPDA_Object::FinishConstruction(FVector2D TilePosition)
{
	if (ObjectType == EObjectType::Table)
	{
		ARestaurantManager* RestaurantManager = Cast<ARestaurantManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ARestaurantManager::StaticClass()));
		RestaurantManager->AddTable(TilePosition);
	}
}

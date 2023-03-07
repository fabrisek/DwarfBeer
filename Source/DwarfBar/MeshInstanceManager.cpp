// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshInstanceManager.h"
#include <LevelEditor.h>

// Sets default values
AMeshInstanceManager::AMeshInstanceManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AMeshInstanceManager::GenerateMeshComponent()
{
    for (int i = 0; i < AllDataToInstance.Num(); i++)
    {
        UInstancedStaticMeshComponent* NewInstance = NewObject<UInstancedStaticMeshComponent>(this, UInstancedStaticMeshComponent::StaticClass(), NAME_None, RF_Transient);
        NewInstance->SetupAttachment(RootComponent);
        AddOwnedComponent(NewInstance);
        NewInstance->RegisterComponent();

        NewInstance->SetStaticMesh(AllDataToInstance[i]->MeshComponent);
        InstancesMap.Add(AllDataToInstance[i]->IdItem, NewInstance);

        if (AllDataToInstance[i]->IdItem == 0)
        {
            NewInstance->PreAllocateInstancesMemory(6000);
            NewInstance->bCastDynamicShadow = false;
            NewInstance->bCastStaticShadow = false;
        }
    }
}

int AMeshInstanceManager::AddNewInstance(int IndexDataItem, FVector2D TilesPosition)
{
    UInstancedStaticMeshComponent** NewInstance = InstancesMap.Find(IndexDataItem);
    if (NewInstance != nullptr && *NewInstance != nullptr)
    {
        const int IndexInstance = (*NewInstance)->AddInstance(FTransform(FRotator(0,0,0), FVector(TilesPosition.X * 100, TilesPosition.Y * 100, 0), FVector(1, 1, 1)), true);
        return IndexInstance;
    }
    return -1;
}

void AMeshInstanceManager::RemoveInstance(int IndexDataItem, FVector2D TilePosition)
{

}


// Called when the game starts or when spawned
void AMeshInstanceManager::BeginPlay()
{
	Super::BeginPlay();
	GenerateMeshComponent();
}

// Called every frame
void AMeshInstanceManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


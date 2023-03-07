// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PDA_Object.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Engine/EngineTypes.h"
#include "MeshInstanceManager.generated.h"

UCLASS()
class DWARFBAR_API AMeshInstanceManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeshInstanceManager();
	void GenerateMeshComponent();
	int AddNewInstance(int IndexDataItem, FVector2D TilesPosition);
	void RemoveInstance(int IndexDataItem, FVector2D TilePosition);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "DATA to Instance")
	TArray<UPDA_Object*> AllDataToInstance;
private:
	UPROPERTY(EditDefaultsOnly, Category = "DATA to Instance")
	TMap<int32, UInstancedStaticMeshComponent*> InstancesMap;
};

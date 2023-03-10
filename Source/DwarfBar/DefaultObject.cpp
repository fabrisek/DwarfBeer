// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultObject.h"

#include "ChunkManager.h"

// Sets default values
ADefaultObject::ADefaultObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void ADefaultObject::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADefaultObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADefaultObject::OnRightClick_Implementation()
{
	AChunkManager* ChunkManager = Cast<AChunkManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AChunkManager::StaticClass()));
	ChunkManager->RemoveObjectAtPosition(TilePosition);
}

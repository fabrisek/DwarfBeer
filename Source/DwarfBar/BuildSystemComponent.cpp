// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UBuildSystemComponent::UBuildSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bIsOnConstruction = false;
	// ...
}


// Called when the game starts
void UBuildSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	DwarfController = Cast<ADwarfBarPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	ChunkManager = Cast<AChunkManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AChunkManager::StaticClass()));
}


// Called every frame
void UBuildSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsOnConstruction && ConstructionObjectInHand != nullptr)
	{
		ConstructionObjectInHand->SetActorLocation(FVector(DwarfController->MousePosition.X*100, DwarfController->MousePosition.Y*100, 100));
		ConstructionObjectInHand->SetActorRotation(FRotator(0,0,0));
	}
	// ...
}

void UBuildSystemComponent::FinishConstruction()
{
	if (ChunkManager->CheckIfTileIsEmpty(FVector2D(DwarfController->MousePosition.X,DwarfController->MousePosition.Y)))
	{
		ConstructionObjectInHand->SetActorEnableCollision(true);
		bIsOnConstruction = false;
		ConstructionObjectInHand = nullptr;
		FTile TileData = ChunkManager->GetTileAtPosition((FVector2D(DwarfController->MousePosition.X,DwarfController->MousePosition.Y)));
		TileData.bIsEmpty = false;
		
		ChunkManager->ChangeTileData(TileData, FVector2D(DwarfController->MousePosition.X,DwarfController->MousePosition.Y));	
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Iferis : %d"), DwarfController->MousePosition.Y);
	}
}

void UBuildSystemComponent::StartConstruction(UPDA_Object* DataObjectRef)
{
	if (!bIsOnConstruction)
	{
		ConstructionObjectInHand = GetWorld()->SpawnActor<ADefaultObject>(ADefaultObject::StaticClass(), DwarfController->MousePosition*100 , FRotator());
		ConstructionObjectInHand->MeshComp->SetStaticMesh(DataObjectRef->MeshComponent);
		ConstructionObjectInHand->SetActorEnableCollision(false);
		bIsOnConstruction = true;
	}
}



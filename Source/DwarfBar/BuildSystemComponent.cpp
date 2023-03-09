// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildSystemComponent.h"
#include "DwarfBarPlayerController.h"
#include "RestaurantManager.h"
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


		//Change le material si la tile est valide
		if (ChunkManager->CheckIfTileIsEmpty(FVector2D(DwarfController->MousePosition.X,DwarfController->MousePosition.Y), DataObjectInHand->SizeGrid.X,DataObjectInHand->SizeGrid.Y,ActualRotation))
		{
			ConstructionObjectInHand->MeshComp->SetMaterial(0,CanConstructMaterial );
		}
			else
			{
				ConstructionObjectInHand->MeshComp->SetMaterial(0, CantConstructMaterial);
			}
	}
	// ...
}


void UBuildSystemComponent::FinishConstruction()
{
	if (ChunkManager->CheckIfTileIsEmpty(FVector2D(DwarfController->MousePosition.X,DwarfController->MousePosition.Y), DataObjectInHand->SizeGrid.X,DataObjectInHand->SizeGrid.Y,ActualRotation))
	{
		TArray<FVector2D> AllPosition = ChunkManager->GetAllTilePositions(FVector2D(DwarfController->MousePosition.X,DwarfController->MousePosition.Y), DataObjectInHand->SizeGrid.X,DataObjectInHand->SizeGrid.Y,ActualRotation);
		ConstructionObjectInHand->SetActorEnableCollision(true);
		bIsOnConstruction = false;
		ConstructionObjectInHand->MeshComp->SetMaterial(0, DataObjectInHand->Material);
		for(int i = 0; i < AllPosition.Num(); i++)
		{
			
			FTile TileData = ChunkManager->GetTileAtPosition(FVector2D(AllPosition[i].X,AllPosition[i].Y));
			TileData.bIsEmpty = false;
			TileData.AllTileBatiment = AllPosition;
			TileData.IdDataRow = DataObjectInHand->IdDataRow;
			ChunkManager->ChangeTileData(TileData, FVector2D(AllPosition[i].X,AllPosition[i].Y));
			
			//TileData.ObjectReference = ConstructionObjectInHand;
		}
		if (DataObjectInHand->ObjectType == EObjectType::Table)
		{
			ARestaurantManager* RestaurantManager = Cast<ARestaurantManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ARestaurantManager::StaticClass()));
			RestaurantManager->AddTable(FVector2D(DwarfController->MousePosition.X,DwarfController->MousePosition.Y));
		}
		
		DataObjectInHand = nullptr;
		ConstructionObjectInHand = nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Position non valide : %d"), DwarfController->MousePosition.Y);
	}
}

void UBuildSystemComponent::ChangeRotation(bool bReverse)
{
	if (bReverse)
	{
		ActualRotation--;
		if(ActualRotation < 0)
			ActualRotation =3;
	}
	else
	{
		ActualRotation++;
		if(ActualRotation > 3)
			ActualRotation = 0;
	}
}

void UBuildSystemComponent::StartConstruction(UPDA_Object* DataObjectRef)
{
	if (!bIsOnConstruction)
	{
		ConstructionObjectInHand = GetWorld()->SpawnActor<ADefaultObject>(ADefaultObject::StaticClass(), DwarfController->MousePosition*100 , FRotator());
		ConstructionObjectInHand->MeshComp->SetStaticMesh(DataObjectRef->MeshComponent);
		ConstructionObjectInHand->SetActorEnableCollision(false);
		DataObjectInHand = DataObjectRef;
		bIsOnConstruction = true;
	}
}



// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildSystemComponent.h"
#include "DwarfBarPlayerController.h"
#include "IContentBrowserSingleton.h"
#include "RestaurantManager.h"
#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"
#include "Structure/FObjectDataTable.h"

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
		ConstructionObjectInHand->SetActorLocation(FVector(DwarfController->MousePosition.X*100 , DwarfController->MousePosition.Y*100 , 0));
		switch (ActualRotation)
		{
		case 0:
			ConstructionObjectInHand->SetActorRotation(FRotator(0,0,0));
			break;
		case 1:
			ConstructionObjectInHand->SetActorRotation(FRotator(0,90,0));
			UE_LOG(LogTemp, Warning, TEXT("Position non valide : %d"), DwarfController->MousePosition.Y);
			break;
		case 2:
			ConstructionObjectInHand->SetActorRotation(FRotator(0,180,0));
			break;
		case 3:
			ConstructionObjectInHand->SetActorRotation(FRotator(0,270,0));
			break;
		default:
			ConstructionObjectInHand->SetActorRotation(FRotator(0,0,0));
			break;
			
		}

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
	if (bIsOnConstruction)
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
			TileData.ObjectReference = ConstructionObjectInHand;
			TileData.Rotation = ActualRotation;
			
			ChunkManager->ChangeTileData(TileData, FVector2D(AllPosition[i].X,AllPosition[i].Y));
			
			//TileData.ObjectReference = ConstructionObjectInHand;
		}
		ConstructionObjectInHand->TypeObject = DataObjectInHand->ObjectType;
		AddObjectInManager(FVector2D(DwarfController->MousePosition.X,DwarfController->MousePosition.Y),DataObjectInHand );
		ConstructionObjectInHand->TilePosition = FVector2D(DwarfController->MousePosition.X,DwarfController->MousePosition.Y);
		DataObjectInHand = nullptr;
		ConstructionObjectInHand = nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Position non valide : %d"), DwarfController->MousePosition.Y);
	}
	}	
}

void UBuildSystemComponent::AddObjectInManager(FVector2D TilePosition, UPDA_Object* DataObject)
{
	ARestaurantManager* RestaurantManager = Cast<ARestaurantManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ARestaurantManager::StaticClass()));
	switch(DataObject->ObjectType)
	{
		case EObjectType::Door:
			RestaurantManager->AddDoor(TilePosition);
			break;

		case EObjectType::Chair:
			RestaurantManager->AddChair(TilePosition);
			break;
		
		case EObjectType::Table:
			RestaurantManager->AddTable(TilePosition);
			break;

		default:

			break;
	}
}

void UBuildSystemComponent::ChangeRotation(bool bReverse)
{
	UE_LOG(LogTemp, Warning, TEXT("OENJENJFF non valide : %d"), DwarfController->MousePosition.Y);
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

void UBuildSystemComponent::StopConstruction()
{
	ConstructionObjectInHand->Destroy();
	ConstructionObjectInHand = nullptr;
	DataObjectInHand = nullptr;
	bIsOnConstruction = false;
}

void UBuildSystemComponent::CopyConstruction()
{
	FTile TileRef = ChunkManager->GetTileAtPosition(FVector2D(DwarfController->MousePosition.X,DwarfController->MousePosition.Y));
	if (TileRef.bIsEmpty == false)
	{
		FString DataTablePath = "/Game/DataObject.DataObject";
		UObject* DataTableObject = StaticLoadObject(UDataTable::StaticClass(), nullptr, *DataTablePath);
		if (UDataTable* DataTable = Cast<UDataTable>(DataTableObject))
		{
			FObjectDataTable* Row = DataTable->FindRow<FObjectDataTable>(TileRef.IdDataRow , TEXT("Cube"));
			StartConstruction(Row->DataObjectRef);
			
		
		}
		}
}

void UBuildSystemComponent::QClick()
{
	if (bIsOnConstruction)
	{
		StopConstruction();
	}
	else
	{
		CopyConstruction();
	}
}



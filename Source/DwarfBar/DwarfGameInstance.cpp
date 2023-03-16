// Fill out your copyright notice in the Description page of Project Settings.


#include "DwarfGameInstance.h"



void UDwarfGameInstance::OnStart()
{
	Super::OnStart();
	FString DataTablePath = "/Game/DataObject.DataObject";
	UObject* DataTableObject = StaticLoadObject(UDataTable::StaticClass(), nullptr, *DataTablePath);
					
	if (!DataTableObject)
	{
		UE_LOG(LogTemp, Error, TEXT("DataTable not found"));
		return;
	}
	
	DataTable = Cast<UDataTable>(DataTableObject);
}

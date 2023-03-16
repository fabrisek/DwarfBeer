// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "DwarfGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DWARFBAR_API UDwarfGameInstance : public UGameInstance
{
	GENERATED_BODY()
	virtual void OnStart() override;
public:
	UPROPERTY(EditAnywhere);
	UDataTable* DataTable;
};

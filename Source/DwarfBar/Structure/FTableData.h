#pragma once
#include "CoreMinimal.h"
#include "FTableData.generated.h"
USTRUCT(BlueprintType)
struct FTableData
{
	GENERATED_USTRUCT_BODY()
	
	FTableData()
	{
		TilePosition = FVector2D(INT_MAX,INT_MAX);
		bBusyTable = false;
		ChairPosition = TArray<FVector2D>();
	}

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Info)
	FVector2D TilePosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Info)
	TArray<FVector2D> ChairPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Info)
	bool bBusyTable;

	friend FArchive& operator<<(FArchive& Archive, FTableData& Data)
	{
		Archive << Data.ChairPosition;
		Archive << Data.TilePosition;
		Archive << Data.bBusyTable;
		return Archive;
	}
};

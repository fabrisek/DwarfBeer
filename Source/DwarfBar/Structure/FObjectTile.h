#pragma once
#include "CoreMinimal.h"
#include "DwarfBar/DefaultObject.h"
#include "DwarfBar/Enum/ETilePositionType.h"
#include "FObjectTile.generated.h"
USTRUCT(BlueprintType)
struct FObjectTile
{
	GENERATED_USTRUCT_BODY()

	FObjectTile()
	{
		TilePositionType = ETilePositionType::InTile;
		Rotation = 0;
		ObjectDataName = "Name";
		ObjectReference = nullptr;
	}
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Info)
	ETilePositionType TilePositionType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Info)
	int Rotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Info)
	FName ObjectDataName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Info)
	ADefaultObject* ObjectReference;
	

	
	friend FArchive& operator<<(FArchive& Archive, FObjectTile& Data)
	{
		Archive << Data.TilePositionType;
		Archive << Data.Rotation;
		Archive << Data.ObjectDataName;
		return Archive;
	}
};
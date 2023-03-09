#pragma once
#include "CoreMinimal.h"
#include "FTableData.generated.h"
USTRUCT(BlueprintType)
struct FTableData
{
	GENERATED_USTRUCT_BODY()
	FTableData()
	{
		
	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Info)
	FVector2D TilePosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Info)
	TArray<FVector2D> ChairPosition;
};

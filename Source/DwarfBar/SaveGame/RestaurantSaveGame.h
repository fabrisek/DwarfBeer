#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DwarfBar/Structure/FTableData.h"
#include "RestaurantSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class DWARFBAR_API URestaurantSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Info)
	TMap<FVector2D,FTableData> TableData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Info)
	TMap<FVector2D, FVector2D> ChairToTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Info)
	TArray<FVector2D> DoorPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Info)
	bool bRestaurantIsOpen;
};

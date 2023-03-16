#pragma once
#include "CoreMinimal.h"
#include "FCustomers.h"
#include "DwarfBar/Enum/EStateGroupCustomers.h"
#include "FGroupCustomers.generated.h"
USTRUCT(BlueprintType)
struct FGroupCustomers
{
	GENERATED_USTRUCT_BODY()
	
	FGroupCustomers()
	{
		StateGroupCustomers = EStateGroupCustomers::WalkToDoor;
		TablePositionRef = FVector2D();
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Info)
	EStateGroupCustomers StateGroupCustomers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Info)
	FVector2D TablePositionRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Info)
	TArray<FCustomers> AllCustomers;

	friend FArchive& operator<<(FArchive& Archive, FGroupCustomers& Data)
	{
		Archive << Data.StateGroupCustomers;
		Archive << Data.TablePositionRef;
		Archive << Data.AllCustomers;
		
		return Archive;
	}
};

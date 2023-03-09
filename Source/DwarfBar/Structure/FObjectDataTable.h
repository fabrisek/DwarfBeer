#pragma once
#include "CoreMinimal.h"
#include "DwarfBar/PDA_Object.h"
#include "Engine/DataTable.h"
#include "FObjectDataTable.generated.h"

USTRUCT(BlueprintType)
struct FObjectDataTable : public FTableRowBase
{
	FObjectDataTable(): DataObjectRef(nullptr)
	{
	}

	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Info)
	FName ObjectName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Data)
	UPDA_Object* DataObjectRef;
};

#pragma once
#include "DwarfBar/NPC/NpcCharacter.h"
#include "FCustomers.generated.h"
USTRUCT(BlueprintType)
struct FCustomers
{
	GENERATED_USTRUCT_BODY()
	FCustomers()
	{
		NpcCharacterRef = nullptr;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Info)
	ANpcCharacter* NpcCharacterRef;	
	
	friend FArchive& operator<<(FArchive& Archive, FCustomers& Data)
	{
		return Archive;
	}
	
};

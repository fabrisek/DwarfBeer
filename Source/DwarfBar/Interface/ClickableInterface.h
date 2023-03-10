#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ClickableInterface.generated.h"

UINTERFACE(BlueprintType)
class DWARFBAR_API UClickableInterface : public UInterface
{
	GENERATED_BODY()
};

class DWARFBAR_API IClickableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Broadcast")
	void OnLeftClick();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Broadcast")
	void OnRightClick();
};


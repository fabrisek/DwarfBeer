// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DwarfBarCharacter.generated.h"

UCLASS(Blueprintable)
class ADwarfBarCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADwarfBarCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBuildSystemComponent* BuildSystemComponent;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	virtual void BeginPlay() override;
};


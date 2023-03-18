// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DwarfBar/Enum/EObjectType.h"
#include "GameFramework/Actor.h"
#include "Interface/ClickableInterface.h"
#include "DefaultObject.generated.h"

UCLASS()
class DWARFBAR_API ADefaultObject : public AActor, public IClickableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefaultObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UStaticMeshComponent* MeshComp;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FVector2D TilePosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Info)
	EObjectType TypeObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Info)
	int Rotation;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Broadcast")
			void OnRightClick();  // This is the prototype declared in the interface
	virtual void OnRightClick_Implementation() override;
};

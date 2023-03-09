// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChunkManager.h"
#include "PDA_Object.h"
#include "DefaultObject.h"
#include "Components/ActorComponent.h"
#include "BuildSystemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DWARFBAR_API UBuildSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuildSystemComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, Category = "Construction")
	void FinishConstruction();
	void AddObjectInManager(FVector2D TilePosition, UPDA_Object* DataObject);
	UFUNCTION(BlueprintCallable, Category = "Construction")
	void ChangeRotation(bool bReverse);
	int ActualRotation;
	UFUNCTION(BlueprintCallable, Category = "Construction")
	void StartConstruction(UPARAM(DisplayName="DATA Object Ref") UPDA_Object* DataObjectRef);
	UPROPERTY(EditDefaultsOnly, Category = "REFERENCE")
	bool bIsOnConstruction;
	UPROPERTY(EditDefaultsOnly, Category = "REFERENCE")
	UMaterialInterface* CanConstructMaterial;
	UPROPERTY(EditDefaultsOnly, Category = "REFERENCE")
	UMaterialInterface* CantConstructMaterial;
private:
	UPROPERTY(EditDefaultsOnly, Category = "REFERENCE")
	class ADwarfBarPlayerController* DwarfController;
	UPROPERTY(EditDefaultsOnly, Category = "REFERENCE")
	ADefaultObject* ConstructionObjectInHand;
	UPDA_Object* DataObjectInHand;
	UPROPERTY(EditDefaultsOnly, Category = "REFERENCE")
	AChunkManager* ChunkManager;
};

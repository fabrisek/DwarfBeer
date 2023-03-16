// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildSystemComponent.h"
#include "GameFramework/Actor.h"
#include "DwarfBar/Structure/FGroupCustomers.h"
#include "DwarfBar/Structure/FTableData.h"
#include "RestaurantManager.generated.h"

UCLASS()
class DWARFBAR_API ARestaurantManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARestaurantManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Info)
	TMap<FVector2D, FVector2D> ChairToTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Info)
	TArray<FVector2D> DoorPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Info)
	bool bRestaurantIsOpen;
	
	void AddTable(FVector2D TilePosition);
	void AddChair(FVector2D TilePosition);
	void RemoveTable(FVector2D TilePosition);
	void RemoveChair(FVector2D TilePosition);
	void AddDoor(FVector2D TilePosition);
	void RemoveDoor(FVector2D TilePosition);

	UFUNCTION(BlueprintCallable, Category = "Manage Restaurant")
	void OpenRestaurant();
	UFUNCTION(BlueprintCallable, Category = "Manage Restaurant")
	void CloseRestaurant();
	UFUNCTION(BlueprintCallable, Category = "Manage Restaurant")
	void KickCustomers();

	void CheckIfNeedCustomers();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Wearable)
	void SpawnCustomers(int Amount);
	virtual void SpawnCustomers_Implementation(int Amount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Info)
	TMap<FVector2D,FTableData> TableData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Info)
	TArray<FGroupCustomers> GroupCustomers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Info)
	TArray<ANpcCharacter*> AllNpc;

	UFUNCTION(BlueprintCallable, Category = "Get Data")
	void AddCustomer(ANpcCharacter* NpcRef);
	
	UFUNCTION(BlueprintCallable, Category = "Get Data")
	FTableData GetFreeTable(int CustomerCount);

	UFUNCTION(BlueprintCallable, Category = "Get Data")
	int AddGroup(FGroupCustomers NewGroupCustomers);

	UFUNCTION(BlueprintCallable, Category = "Get Data")
	FGroupCustomers GetGroupCustomers(int Index);

private:
	
	UPROPERTY()
	AChunkManager* ChunkManager;

	
	void SaveGame();
	void CheckIfSaveExist();
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildSystemComponent.h"

#include "DefaultObject.h"

// Sets default values for this component's properties
UBuildSystemComponent::UBuildSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBuildSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBuildSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBuildSystemComponent::FinishConstruction()
{
}

void UBuildSystemComponent::StartConstruction(UPDA_Object DataObjectRef)
{
	//GetWorld()->SpawnActor<ADefaultObject>(ADefaultObject::StaticClass(), , FRotator());
}


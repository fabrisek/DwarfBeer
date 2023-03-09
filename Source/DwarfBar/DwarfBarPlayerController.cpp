// Copyright Epic Games, Inc. All Rights Reserved.

#include "DwarfBarPlayerController.h"

ADwarfBarPlayerController::ADwarfBarPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
}

void ADwarfBarPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}



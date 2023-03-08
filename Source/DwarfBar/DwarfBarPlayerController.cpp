// Copyright Epic Games, Inc. All Rights Reserved.

#include "DwarfBarPlayerController.h"

#include "BuildSystemComponent.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "DwarfBarCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


ADwarfBarPlayerController::ADwarfBarPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
}

void ADwarfBarPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	CharacterRef = Cast<ADwarfBarCharacter>(GetPawn());
}

void ADwarfBarPlayerController::LeftClick()
{
	if (CharacterRef->BuildSystemComponent->bIsOnConstruction)
	{
		CharacterRef->BuildSystemComponent->FinishConstruction();
	}
}

void ADwarfBarPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ADwarfBarPlayerController::LeftClick);
	}
}


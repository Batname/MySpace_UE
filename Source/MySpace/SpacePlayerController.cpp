// Fill out your copyright notice in the Description page of Project Settings.


#include "SpacePlayerController.h"


void ASpacePlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI());
}
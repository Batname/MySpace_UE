// Fill out your copyright notice in the Description page of Project Settings.


#include "MySpaceGameModeBase.h"
#include "Blueprint/UserWidget.h"

void AMySpaceGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);
	UE_LOG(LogTemp, Warning, TEXT("AMySpaceGameModeBase::BeginPlay"));
}

void AMySpaceGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

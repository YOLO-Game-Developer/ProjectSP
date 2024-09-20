// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SPPlayerController.h"
#include "Blueprint/UserWidget.h"

ASPPlayerController::ASPPlayerController()
{
}

void ASPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	InitWidget();
}

void ASPPlayerController::SetUI(bool InVisible)
{
	if (EndedUI == nullptr) return;

	if (InVisible)
	{
		EndedUI->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		EndedUI->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ASPPlayerController::RestartLevel()
{
	Super::RestartLevel();

	SetUI(false);
}

void ASPPlayerController::InitWidget()
{
	EndedUI = CreateWidget<UUserWidget>(GetWorld(), EndedUIClass);
	EndedUI->AddToViewport(5);
	EndedUI->SetVisibility(ESlateVisibility::Visible);

	if (EndedUI)
	{
		EndedUI->SetVisibility(ESlateVisibility::Collapsed);
	}
}

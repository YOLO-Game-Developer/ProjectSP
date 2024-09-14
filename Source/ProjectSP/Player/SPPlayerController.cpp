// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SPPlayerController.h"

ASPPlayerController::ASPPlayerController()
{
}

void ASPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
}

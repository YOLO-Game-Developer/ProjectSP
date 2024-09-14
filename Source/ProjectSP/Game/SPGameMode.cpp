// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SPGameMode.h"
#include "Character/SPCharacterPlayer.h"
#include "Player/SPPlayerController.h"
#include "Player/SPPlayerState.h"

ASPGameMode::ASPGameMode()
{
	static ConstructorHelpers::FClassFinder<USkeletalMesh> PawnClassRef(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_SPPlayerPawn.BP_SPPlayerPawn'"));

	if (PawnClassRef.Class)
	{
		DefaultPawnClass = PawnClassRef.Class;
	}

	PlayerControllerClass = ASPPlayerController::StaticClass();

	PlayerStateClass = ASPPlayerState::StaticClass();
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SPCharacterNonPlayer.h"
#include "Character/SPStatComponent.h"
#include "AI/SPAIController.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
ASPCharacterNonPlayer::ASPCharacterNonPlayer()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny_Simple.SKM_Manny_Simple'"));

	if (SkeletalMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(SkeletalMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimClassRef(TEXT("/Game/Animation/ABP_SPAnimInstance.ABP_SPAnimInstance_C"));

	if (AnimClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimClassRef.Class);
	}

	AIControllerClass = ASPAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));

	UAISenseConfig_Sight* SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	AIPerception->ConfigureSense(*SightConfig);
	AIPerception->OnPerceptionUpdated.AddDynamic(this, &ASPCharacterNonPlayer::PerceptionUpdated);
}

void ASPCharacterNonPlayer::BeginPlay()
{
	Super::BeginPlay();

	Stat->InitStat(100.f, 5.f, 0.f); //임시로 지정 게임 데이터로 변경 예정
}

void ASPCharacterNonPlayer::PerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
}

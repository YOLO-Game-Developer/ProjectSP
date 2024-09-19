// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SPCharacterNonPlayer.h"
#include "Character/SPStatComponent.h"
#include "Character/SPSkillComponent.h"
#include "AI/SPAIController.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
ASPCharacterNonPlayer::ASPCharacterNonPlayer()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny_Simple.SKM_Manny_Simple'"));

	if (SkeletalMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(SkeletalMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimClassRef(TEXT("/Game/Animation/ABP_SPZombie.ABP_SPZombie_C"));

	if (AnimClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimClassRef.Class);
	}

	AIControllerClass = ASPAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCharacterMovement()->MaxWalkSpeed = 350.f;
}

void ASPCharacterNonPlayer::BeginPlay()
{
	Super::BeginPlay();

	Stat->InitStat(100.f, 5.f, 90.f); //임시로 지정 게임 데이터로 변경 예정
}

void ASPCharacterNonPlayer::InitSpawn(FOnAIDeathCountChanged& InOnAIDeathCountChanged)
{
	OnAIDeathCountChanged = InOnAIDeathCountChanged;
}

void ASPCharacterNonPlayer::Dead()
{
	Super::Dead();
	if (OnAIDeathCountChanged.IsBound())
	{
		OnAIDeathCountChanged.Execute();
	}
}

float ASPCharacterNonPlayer::GetPatrolRadius()
{
	return 1000.f;
}

float ASPCharacterNonPlayer::GetAttackDamage()
{
	return Stat->GetAttack();
}

void ASPCharacterNonPlayer::SetAIAttackDelegate(FAICharacterAttackFinished& InOnAttackFinished)
{
	if (OnAttackFinished.IsBound() == false)
	{
		OnAttackFinished = InOnAttackFinished;
	}
}

void ASPCharacterNonPlayer::AttackByAI()
{
	bIsAttacking = true;
	Skill->Attack();

	UAnimInstance* AnimInstance = Cast<UAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance->OnMontageEnded.IsBound() == false)
	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &ASPCharacterNonPlayer::OnSkillMontageEnded);
	}
}

bool ASPCharacterNonPlayer::IsAttacking()
{
	return bIsAttacking;
}

void ASPCharacterNonPlayer::OnSkillMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (OnAttackFinished.IsBound())
	{
		bIsAttacking = false;
		OnAttackFinished.Execute();
	}
}

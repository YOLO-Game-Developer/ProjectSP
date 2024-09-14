// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SPCharacterPlayer.h"
#include "Character/SPHeroComponent.h"
#include "Character/SPStatComponent.h"
#include "Character/SPSkillComponent.h"
#include "Player/SPPlayerController.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

// Sets default values
ASPCharacterPlayer::ASPCharacterPlayer()
{
	SPHeroComponent = CreateDefaultSubobject<USPHeroComponent>(TEXT("InputComponent"));
	Stat = CreateDefaultSubobject<USPStatComponent>(TEXT("StatComponent"));
	Skill = CreateDefaultSubobject<USPSkillComponent>(TEXT("SkillComponent"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny_Simple.SKM_Manny_Simple'"));

	if (SkeletalMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(SkeletalMeshRef.Object);
	}

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = false; //QuaterView는 회전하지 않는다.
	SpringArm->TargetArmLength = 500.f;
	SpringArm->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
}

// Called to bind functionality to input
void ASPCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (SPHeroComponent)
	{
		SPHeroComponent->SetupPlayerInputComponent(PlayerInputComponent);
	}
}

void ASPCharacterPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void ASPCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	//Enhanced 등록 
	SPHeroComponent->InitInputMappingContext();
	Stat->InitStat(100.f, 20.f, 60.f); //임시로 지정 게임 데이터로 변경 예정
}

void ASPCharacterPlayer::Attack()
{
	if (Skill == nullptr) return;

	Skill->Attack();
}

void ASPCharacterPlayer::DisplayAttackRange()
{
	if (Skill == nullptr) return;

	Skill->DisplayAttackRange();
}

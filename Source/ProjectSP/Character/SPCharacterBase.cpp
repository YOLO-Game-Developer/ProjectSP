// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SPCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/SPGetStatInterface.h"
#include "Physics/SPCollision.h"
#include "Character/SPStatComponent.h"
#include "Character/SPSkillComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASPCharacterBase::ASPCharacterBase()
{
	//Pawn - ���ͺ� ����
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->MaxWalkSpeed = 450.f;
	GetCharacterMovement()->JumpZVelocity = 0.f; //���� �� �� ����.
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.0f, 0.f); //FORCEINLINE FRotator(T InPitch, T InYaw, T InRoll);
	GetCharacterMovement()->AirControl = 0.35f; //������ ���⶧���� ���߿� �� Ȯ���� ������, ���� ���� ����.
	GetCharacterMovement()->bOrientRotationToMovement = true; //ĳ���ͳ� ���Ͱ� �̵��� �� �� �������� ȸ���� ����(���콺�� ���� ȸ���� �����ϵ��� ������)
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f; //���� ���ߴ� ȿ�� 
	GetCharacterMovement()->bWantsToCrouch = false;
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	//CapsuleComponent
	GetCapsuleComponent()->InitCapsuleSize(25.f, 90.0f);
	GetCapsuleComponent()->SetCollisionProfileName(CPROFILE_SPCAPSULE); //���߿� ���� ����

	//SkeletalMesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.0f, -90.f, 0.f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	Stat = CreateDefaultSubobject<USPStatComponent>(TEXT("StatComponent"));
	Skill = CreateDefaultSubobject<USPSkillComponent>(TEXT("SkillComponent"));
}

float ASPCharacterBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	ISPGetStatInterface* Interface = Cast<ISPGetStatInterface>(this);

	if (Interface)
	{
		USPStatComponent *TmpStat = Interface->GetStat();
		
		float HP = TmpStat->GetHP();

		if (TmpStat->GetHP() <= 0.f)
		{
			Dead();
			return 0.f;
		}
		TmpStat->SetHP(HP - FinalDamage);
	}
	//float State�� ������ 
	return FinalDamage;
}

USPStatComponent* ASPCharacterBase::GetStat()
{
	return Stat;
}

void ASPCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}


bool ASPCharacterBase::IsPlayMontage(UAnimMontage* InMontage)
{
	UAnimInstance* AnimInstance = Cast<UAnimInstance>(GetMesh()->GetAnimInstance());

	if (AnimInstance)
	{
		return AnimInstance->Montage_IsPlaying(InMontage);
	}
	return false;
}

void ASPCharacterBase::Dead()
{
	UAnimInstance* AnimInstance = Cast<UAnimInstance>(GetMesh()->GetAnimInstance());

	if (AnimInstance)
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		AnimInstance->Montage_Play(DeathMontage, 1.f);
		this->SetLifeSpan(3.0f);
	}

}

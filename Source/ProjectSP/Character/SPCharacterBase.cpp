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
	//Pawn - 쿼터뷰 예정
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->MaxWalkSpeed = 450.f;
	GetCharacterMovement()->JumpZVelocity = 0.f; //점프 할 수 없음.
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.0f, 0.f); //FORCEINLINE FRotator(T InPitch, T InYaw, T InRoll);
	GetCharacterMovement()->AirControl = 0.35f; //점프가 없기때문에 공중에 날 확률은 적지만, 있을 수도 있음.
	GetCharacterMovement()->bOrientRotationToMovement = true; //캐릭터나 액터가 이동할 때 그 방향으로 회전을 수행(마우스에 따라서 회전을 수행하도록 도와줌)
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f; //점차 멈추는 효과 
	GetCharacterMovement()->bWantsToCrouch = false;
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	//CapsuleComponent
	GetCapsuleComponent()->InitCapsuleSize(25.f, 90.0f);
	GetCapsuleComponent()->SetCollisionProfileName(CPROFILE_SPCAPSULE); //나중에 변경 예정

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
	//float State를 가져옴 
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

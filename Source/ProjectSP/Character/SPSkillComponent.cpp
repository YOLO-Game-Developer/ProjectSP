// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SPSkillComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/DecalComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Character/SPStatComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/SPCharacterPlayer.h"
#include "Engine/DamageEvents.h" 

USPSkillComponent::USPSkillComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), MinDegree(-30.f), MaxDegree(30.f)
{
	static ConstructorHelpers::FClassFinder<AActor> SkillDecalRef(TEXT("/Game/Blueprints/BP_SPSkillPlane.BP_SPSkillPlane_C"));

	if (SkillDecalRef.Class)
	{
		SkillDecalClass = SkillDecalRef.Class;
	}

}

void USPSkillComponent::BeginPlay()
{
	Super::BeginPlay();

	ASPCharacterPlayer*Character = GetPawn<ASPCharacterPlayer>();

	if (Character)
	{
		FVector Location = Character->GetActorLocation();
		FActorSpawnParameters Params;
		SkillDecalActor = GetWorld()->SpawnActor<AActor>(SkillDecalClass, Location, FRotator(0.f,90.f,0.f), Params);
		SkillDecalActor->SetActorHiddenInGame(true);
	}

}

void USPSkillComponent::CheckAttackCollision()
{
	//Overlap
	ASPCharacterBase* Character = GetPawn<ASPCharacterBase>();

	if (Character)
	{
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		TArray<AActor*> IgnoreActors;
		TArray<AActor*> OutActors;

		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
		IgnoreActors.Add(Character);

		FVector Location = Character->GetActorLocation();

		float Damage = Character->GetStat()->GetAttack();
		bool Result = UKismetSystemLibrary::SphereOverlapActors(GetWorld(), Location, 100.f, ObjectTypes, nullptr, IgnoreActors, OutActors);
		if (Result)
		{
			for (AActor* Actor : OutActors)
			{
				//�浹 üũ
				if (IsHitByAttack(Character, Actor))
				{
					//�������� ������.
					FDamageEvent DamageEvent;

					Actor->TakeDamage(Damage, DamageEvent, Character->GetController(), Character);
				}
			}
		}
	}
}


bool USPSkillComponent::IsHitByAttack(AActor* CurrentActor, AActor* OtherActor)
{
	FVector Origin = CurrentActor->GetActorLocation();
	FVector Dest = OtherActor->GetActorLocation();

	Origin.Z = 0;
	Dest.Z = 0;
	
	FVector ForwardVector = CurrentActor->GetActorForwardVector(); // ���� Actor�� �ٶ󺸴� ����
	FVector ToTarget = (Dest - Origin).GetSafeNormal(); // Ÿ�� ���� ����ȭ

	float DotResult = FVector::DotProduct(ForwardVector, ToTarget); //����

	float Radian = FMath::Acos(DotResult); //������ ���ؼ� Acos�� ���ָ� ���� �� ����

	// ������ ������ ��ȯ
	float Angle = FMath::RadiansToDegrees(Radian); //������ Degree�� �ٲ��ָ�

	bool IsHit = MinDegree <= Angle && Angle <= MaxDegree;

	return IsHit; //�ش� ���� ���̿� ������ ��Ʈ ������ �����Ѵ�
}

void USPSkillComponent::Attack()
{
	//���� ���⼭ ������ �����Ѵ�.
	ASPCharacterBase* Character = GetPawn<ASPCharacterBase>();
	if (Character)
	{
		if (Character->IsPlayMontage(SkillMontage)) return;

		UAnimInstance* AnimInstance = Cast<UAnimInstance>(Character->GetMesh()->GetAnimInstance());

		if (AnimInstance)
		{
			AnimInstance->Montage_Play(SkillMontage, 1.f);
		}

		if (SkillDecalActor)
		{
			SkillDecalActor->SetActorHiddenInGame(true);
		}
	}

	MinDegree = -(Character->GetStat()->GetRadiusOfAttack() / 2.f);
	MaxDegree = (Character->GetStat()->GetRadiusOfAttack() / 2.f);

	CheckAttackCollision();
}

void USPSkillComponent::DisplayAttackRange()
{
	ASPCharacterPlayer* Character = GetPawn<ASPCharacterPlayer>();
	if (Character)
	{
		if (Character->IsPlayMontage(SkillMontage)) return;

		FVector Location = Character->GetActorLocation();

		Location.Z -= 50.f;
		FRotator Rotation = Character->GetActorRotation() + FRotator(0.f,90.f,0.f);

		SkillDecalActor->SetActorRotation(Rotation);
		SkillDecalActor->SetActorLocation(Location);

		SkillDecalActor->SetActorHiddenInGame(false);
	}

	//���� ���⼭ ��Į�� �׸���.
	//14�Ͽ� Debug Draw�� �׸� ���� -> �׸���, 15�� ���ῡ ���ƿͼ� Decal�� ��ü 
}

void USPSkillComponent::DrawDebugCircleArcFanWithDirection(UWorld* World, FVector Center, FVector Direction, float Radius, float StartAngle, float EndAngle, int32 Segments, FColor Color, float Thickness, bool bPersistentLines, float LifeTime)
{
	FVector Forward = Direction.GetSafeNormal();

	// Calculate right vector for generating fan points around the direction
	FVector Right = FVector::CrossProduct(Forward, FVector::UpVector);

	FVector PreviousPoint = Center;

	float AngleStep = (EndAngle - StartAngle) / Segments; //���� ǥ���ϱ� ���ؼ� �󸶳� �׷����ϴ��� ǥ��


	float Angle = FMath::DegreesToRadians(StartAngle); //���� �ޱ� ���� �������� �ٲٰ�
	FVector RotatedDirection = Forward * FMath::Cos(Angle) + Right * FMath::Sin(Angle); //���� ��ġ�� ������
	FVector CurrentPoint = Center + RotatedDirection * Radius; //���� ���������� �󸶳� �̵��ؾ��ϴ°��� ǥ��

	DrawDebugLine(World, PreviousPoint, CurrentPoint, Color, bPersistentLines, LifeTime, 0, Thickness);

	// Loop through each segment to draw the arc
	for (int32 i = 0; i <= Segments; i++)
	{
		// Calculate current angle in radians, ���� �׸���
		Angle = FMath::DegreesToRadians(StartAngle + i * AngleStep);

		// Calculate the point on the arc based on direction and right vector
		RotatedDirection = Forward * FMath::Cos(Angle) + Right * FMath::Sin(Angle);
		CurrentPoint = Center + RotatedDirection * Radius;

		// Draw the line connecting this point to the previous one
		if (i > 0)
		{
			DrawDebugLine(World, PreviousPoint, CurrentPoint, Color, bPersistentLines, LifeTime, 0, Thickness);
		}

		PreviousPoint = CurrentPoint;
	}

	// Draw lines connecting the arc points to the center to complete the fan shape
	DrawDebugLine(World, Center, PreviousPoint, Color, bPersistentLines, LifeTime, 0, Thickness);
}

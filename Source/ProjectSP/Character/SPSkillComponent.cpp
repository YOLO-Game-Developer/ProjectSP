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
				//충돌 체크
				if (IsHitByAttack(Character, Actor))
				{
					//데미지를 입힌다.
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
	
	FVector ForwardVector = CurrentActor->GetActorForwardVector(); // 현재 Actor의 바라보는 방향
	FVector ToTarget = (Dest - Origin).GetSafeNormal(); // 타겟 방향 정규화

	float DotResult = FVector::DotProduct(ForwardVector, ToTarget); //내적

	float Radian = FMath::Acos(DotResult); //내적에 대해서 Acos을 해주면 라디안 값 나옴

	// 라디안을 각도로 변환
	float Angle = FMath::RadiansToDegrees(Radian); //라디안을 Degree로 바꿔주면

	bool IsHit = MinDegree <= Angle && Angle <= MaxDegree;

	return IsHit; //해당 값이 사이에 들어가는지 히트 판정을 수행한다
}

void USPSkillComponent::Attack()
{
	//실제 여기서 공격을 수행한다.
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

	//실제 여기서 데칼을 그린다.
	//14일엔 Debug Draw를 그릴 예정 -> 그리고, 15일 저녁에 돌아와서 Decal로 대체 
}

void USPSkillComponent::DrawDebugCircleArcFanWithDirection(UWorld* World, FVector Center, FVector Direction, float Radius, float StartAngle, float EndAngle, int32 Segments, FColor Color, float Thickness, bool bPersistentLines, float LifeTime)
{
	FVector Forward = Direction.GetSafeNormal();

	// Calculate right vector for generating fan points around the direction
	FVector Right = FVector::CrossProduct(Forward, FVector::UpVector);

	FVector PreviousPoint = Center;

	float AngleStep = (EndAngle - StartAngle) / Segments; //원을 표현하기 위해서 얼마나 그려야하는지 표현


	float Angle = FMath::DegreesToRadians(StartAngle); //시작 앵글 값을 라디안으로 바꾸고
	FVector RotatedDirection = Forward * FMath::Cos(Angle) + Right * FMath::Sin(Angle); //시작 위치를 가져옴
	FVector CurrentPoint = Center + RotatedDirection * Radius; //현재 시작점에서 얼마나 이동해야하는가를 표현

	DrawDebugLine(World, PreviousPoint, CurrentPoint, Color, bPersistentLines, LifeTime, 0, Thickness);

	// Loop through each segment to draw the arc
	for (int32 i = 0; i <= Segments; i++)
	{
		// Calculate current angle in radians, 원형 그리기
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

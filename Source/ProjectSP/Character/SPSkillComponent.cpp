// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SPSkillComponent.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/DecalComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

USPSkillComponent::USPSkillComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
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

	ACharacter *Character = GetPawn<ACharacter>();

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
	ACharacter* Character = GetPawn<ACharacter>();

	if (Character)
	{
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		TArray<AActor*> IgnoreActors;
		TArray<AActor*> OutActors;

		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
		IgnoreActors.Add(Character);

		FVector Location = Character->GetActorLocation();

		bool Result = UKismetSystemLibrary::SphereOverlapActors(GetWorld(), Location, 100.f, ObjectTypes, nullptr, IgnoreActors, OutActors);
		UE_LOG(LogTemp, Log, TEXT("1"));
		if (Result)
		{
			UE_LOG(LogTemp, Log, TEXT("2"));
			for (AActor* Actor : OutActors)
			{
				//�浹 üũ
				if (IsHitByAttack(Character, Actor))
				{
					//�������� ������.
				}
			}
		}
	}
}

bool USPSkillComponent::IsHitByAttack(AActor* CurrentActor, AActor* OtherActor)
{


	return false;
}

void USPSkillComponent::OnSkillMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	ACharacter* Character = GetPawn<ACharacter>();
	if (Character)
	{
		Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}
}

void USPSkillComponent::Attack()
{
	//���� ���⼭ ������ �����Ѵ�.
	ACharacter* Character = GetPawn<ACharacter>();
	if (Character)
	{
		UAnimInstance* AnimInstance = Cast<UAnimInstance>(Character->GetMesh()->GetAnimInstance());

		if (AnimInstance)
		{
			AnimInstance->Montage_Play(SkillMontage, 1.f);
			AnimInstance->OnMontageEnded.AddDynamic(this, &USPSkillComponent::OnSkillMontageEnded);
		}

		CheckAttackCollision();
	}
	SkillDecalActor->SetActorHiddenInGame(true);
}

void USPSkillComponent::DisplayAttackRange()
{
	ACharacter* Character = GetPawn<ACharacter>();
	if (Character)
	{

		Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		FVector Location = Character->GetActorLocation();

		Location.Z -= 50.f;
		FRotator Rotation = Character->GetActorRotation() + FRotator(0.f,90.f,0.f);

		SkillDecalActor->SetActorRotation(Rotation);
		SkillDecalActor->SetActorLocation(Location);
	}

	SkillDecalActor->SetActorHiddenInGame(false);
	//���� ���⼭ ��Į�� �׸���.
	//14�Ͽ� Debug Draw�� �׸� ���� -> �׸���, 15�� ���ῡ ���ƿͼ� Decal�� ��ü 

	//ACharacter* Owner = GetPawn<ACharacter>();

	//if (Owner)
	//{
	//	FVector Center = Owner->GetActorLocation();
	//	FVector Direction = Owner->GetActorForwardVector();
	//	float Radius = 300.f;
	//	FColor Color = FColor::Red;

	//	DrawDebugCircleArcFanWithDirection(GetWorld(), Center, Direction, Radius, -30.f, 30.0f, 20, FColor::Red, 2.0f,true); 60��
	//}
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

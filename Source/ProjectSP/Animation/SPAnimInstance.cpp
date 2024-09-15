// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/SPAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

USPAnimInstance::USPAnimInstance() :bIsIdle(false), MovingThreshold(3.f)
{
	
}

void USPAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACharacter>(GetOwningActor());
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void USPAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Owner)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D(); //Z값을 제외한 X/Y에 대한 크기
		bIsIdle = GroundSpeed < MovingThreshold; //x-y에 대한 크기가 3.0보다 작을 시 Idle로 판정
	}
}

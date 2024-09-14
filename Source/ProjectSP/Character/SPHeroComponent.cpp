// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SPHeroComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


#include "Character/SPCharacterPlayer.h"
#include "Player/SPPlayerController.h"
#include "GameFramework/Controller.h"

USPHeroComponent::USPHeroComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputContextMappingRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Inputs/IMC_Default.IMC_Default'"));

	if (InputContextMappingRef.Object)
	{
		InputMappingContext = InputContextMappingRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/Input/IA_Move.IA_Move'"));

	if (MoveActionRef.Object)
	{
		MoveAction = MoveActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> AttackActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/Input/IA_Attack.IA_Attack'"));

	if (AttackActionRef.Object)
	{
		AttackAction = AttackActionRef.Object;
	}

	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void USPHeroComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PC = GetController<ASPPlayerController>();
	Owner = GetPawn<ASPCharacterPlayer>();

	if (PlayerInputComponent)
	{
		UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &USPHeroComponent::OnMoveInputStarted);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &USPHeroComponent::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &USPHeroComponent::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Canceled, this, &USPHeroComponent::OnSetDestinationReleased);
	
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &USPHeroComponent::OnAttackInputStarted);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Completed, this, &USPHeroComponent::OnAttackInputReleased);

	}
}

void USPHeroComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USPHeroComponent::InitInputMappingContext()
{
	if (PC == nullptr) return;

	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
	{
		SubSystem->ClearAllMappings(); //��� ���� ���
		UInputMappingContext* NewMappingContext = InputMappingContext;

		if (NewMappingContext)
		{
			SubSystem->AddMappingContext(NewMappingContext, 0);
		}
	}

}

void USPHeroComponent::OnMoveInputStarted()
{
	if (PC == nullptr) return;
	if (Owner == nullptr) return;

	PC->StopMovement(); //������ �� ���� �������� ���߰�,
	
	//start - completed�� �����ؾ��ϳ�?
}

void USPHeroComponent::OnSetDestinationTriggered()
{
	if (PC == nullptr || Owner == nullptr) return;
	
	FollowTime += GetWorld()->GetDeltaSeconds();

	FHitResult HitResult;
	bool bHitSuccessful = PC->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, HitResult);

	if (bHitSuccessful)
	{
		CachedDestination = HitResult.Location;
	}

	//Ŭ���� ������ ȸ���ϵ��� �Ѵ�.
	FVector Direction = CachedDestination - Owner->GetActorLocation();
	FRotator LookAtRotation = UKismetMathLibrary::MakeRotFromX(Direction);
	LookAtRotation.Pitch = 0.f;
	LookAtRotation.Roll = 0.f;
	Owner->SetActorRotation(LookAtRotation); //�ٶ󺸴� �������� ȸ��

	FVector Destination = (Direction).GetSafeNormal();
	Owner->AddMovementInput(Destination); //�̵�
}

void USPHeroComponent::OnSetDestinationReleased()
{
	if (PC == nullptr) return;

	if (FollowTime <= ShortPressThreshold)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(PC, CachedDestination);
	}

	FollowTime = 0.f;
}

void USPHeroComponent::OnAttackInputStarted()
{
	UE_LOG(LogTemp, Log, TEXT("Attack Started Decal"));
	//ĳ���Ͱ� �ٶ󺸴� �������� Decal
}

void USPHeroComponent::OnAttackInputReleased()
{
	UE_LOG(LogTemp, Log, TEXT("Attack!"));
}

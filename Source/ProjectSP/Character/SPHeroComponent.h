// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/PawnComponent.h"
#include "SPHeroComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSP_API USPHeroComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	USPHeroComponent(const FObjectInitializer& ObjectInitializer);

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

	virtual void BeginPlay() override;

	//멤버 변수 설정
	void InitInputMappingContext();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> InputMappingContext;

protected:
	//InputAction - Move
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	FVector CachedDestination; //목적지를 캐싱
	float FollowTime; //얼마나 길게 눌렀는지를 체크하기 위함.

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold; //누른 초의 기준

protected:
	void OnMoveInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> AttackAction;


protected:
	void OnAttackInputStarted();
	void OnAttackInputReleased();

protected:

	UPROPERTY()
	TObjectPtr<class ASPCharacterPlayer> Owner;
	UPROPERTY()
	TObjectPtr<class APlayerController> PC;

};

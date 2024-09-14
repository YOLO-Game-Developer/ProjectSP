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

	//��� ���� ����
	void InitInputMappingContext();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> InputMappingContext;

protected:
	//InputAction - Move
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	FVector CachedDestination; //�������� ĳ��
	float FollowTime; //�󸶳� ��� ���������� üũ�ϱ� ����.

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold; //���� ���� ����

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

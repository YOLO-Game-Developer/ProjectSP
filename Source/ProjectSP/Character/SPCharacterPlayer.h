// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SPCharacterBase.h"
#include "SPCharacterPlayer.generated.h"

UCLASS()
class PROJECTSP_API ASPCharacterPlayer : public ASPCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASPCharacterPlayer();

	void Attack();
	void DisplayAttackRange();
protected:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

protected:

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USPHeroComponent> SPHeroComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USPStatComponent> Stat;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USPSkillComponent> Skill;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<class USpringArmComponent> SpringArm;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Player")
	TObjectPtr<class ASPPlayerController> PC;

};

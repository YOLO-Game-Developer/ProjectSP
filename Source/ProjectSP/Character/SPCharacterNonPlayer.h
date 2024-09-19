// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/SPAIInterface.h"
#include "Character/SPCharacterBase.h"
#include "SPCharacterNonPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSP_API ASPCharacterNonPlayer : public ASPCharacterBase, public ISPAIInterface
{
	GENERATED_BODY()
	
public:
	ASPCharacterNonPlayer();

	virtual void BeginPlay() override;

protected:

	virtual float GetPatrolRadius();
	virtual float GetAttackDamage();
	virtual void SetAIAttackDelegate(FAICharacterAttackFinished& InOnAttackFinished);
	virtual void AttackByAI();
	virtual bool IsAttacking();
protected:
	FAICharacterAttackFinished OnAttackFinished;

protected:
	UFUNCTION()
	void OnSkillMontageEnded(UAnimMontage* Montage, bool bInterrupted);
};

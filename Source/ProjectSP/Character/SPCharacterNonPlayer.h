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
	virtual void InitSpawn(FOnAIDeathCountChanged& InOnAIDeathCountChanged);

protected:

	virtual void Dead() override;
	virtual float GetPatrolRadius();
	virtual float GetAttackDamage();
	virtual void SetAIAttackDelegate(FAICharacterAttackFinished& InOnAttackFinished);
	virtual void AttackByAI();
	virtual bool IsAttacking();
protected:
	FAICharacterAttackFinished OnAttackFinished;
	FOnAIDeathCountChanged OnAIDeathCountChanged;
protected:
	UFUNCTION()
	void OnSkillMontageEnded(UAnimMontage* Montage, bool bInterrupted);

};

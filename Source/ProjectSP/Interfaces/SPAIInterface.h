// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SPAIInterface.generated.h"

// This class does not need to be modified.
DECLARE_DELEGATE(FOnAIDeathCountChanged)
DECLARE_DELEGATE(FAICharacterAttackFinished);
UINTERFACE(MinimalAPI)
class USPAIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTSP_API ISPAIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual float GetPatrolRadius() = 0;
	virtual float GetAttackDamage() = 0;
	virtual void SetAIAttackDelegate(FAICharacterAttackFinished& InOnAttackFinished) = 0;
	virtual void InitSpawn(FOnAIDeathCountChanged& InOnAIDeathCountChanged) = 0;
	virtual void AttackByAI() = 0;


	virtual bool IsAttacking() = 0;
};

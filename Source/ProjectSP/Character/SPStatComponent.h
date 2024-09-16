// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "SPStatComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSP_API USPStatComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	USPStatComponent(const FObjectInitializer& ObjectInitializer);

	void InitStat(float InHP, float InAttack, float InRadiusOfAttack);

	void SetHP(float InHP) { HP = InHP; }
	float GetHP() { return HP; }
	float GetMaxHP() { return MaxHP; }
	float GetAttack() { return Attack; }
	float GetMaxAttack() { return MaxAttack; }
	float GetRadiusOfAttack() { return RadiusOfAttack; }

protected:
	float HP;
	float MaxHP;
	float Attack;
	float MaxAttack;
	float RadiusOfAttack;
};

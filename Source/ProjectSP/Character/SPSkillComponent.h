// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "SPSkillComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSP_API USPSkillComponent : public UPawnComponent
{
	GENERATED_BODY()
	
public:

	void Attack(); //어차피 공격을 늘리더라도 나중에 늘릴 예정

	void DisplayAttackRange();
};

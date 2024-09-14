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

	void Attack(); //������ ������ �ø����� ���߿� �ø� ����

	void DisplayAttackRange();
};

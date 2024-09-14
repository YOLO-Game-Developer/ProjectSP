// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SPCharacterStat.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSP_API USPCharacterStat : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	float HP;
	float Attack;
	float AngleOfAttack;
	
};

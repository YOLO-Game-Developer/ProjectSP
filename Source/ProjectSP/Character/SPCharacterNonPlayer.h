// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SPCharacterBase.h"
#include "Interfaces/SPGetStatInterface.h"
#include "SPCharacterNonPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSP_API ASPCharacterNonPlayer : public ASPCharacterBase, public ISPGetStatInterface
{
	GENERATED_BODY()
	
public:
	virtual class USPStatComponent* GetStat() override;

};

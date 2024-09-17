// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SPCharacterBase.h"
#include "SPCharacterNonPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSP_API ASPCharacterNonPlayer : public ASPCharacterBase
{
	GENERATED_BODY()
	
public:
	ASPCharacterNonPlayer();

	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI)
	TObjectPtr<class UAIPerceptionComponent> AIPerception;

protected:

	UFUNCTION()
	void PerceptionUpdated(const TArray<AActor*>& UpdatedActors);
};

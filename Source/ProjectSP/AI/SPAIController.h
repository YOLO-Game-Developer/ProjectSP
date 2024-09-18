// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SPAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSP_API ASPAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ASPAIController();
	
	void RunAI();
	void StopAI();

	virtual void OnPossess(APawn* InPawn) override;
protected:

	UPROPERTY()
	TObjectPtr<class UBlackboardData> BBAsset;

	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BTAsset;



};

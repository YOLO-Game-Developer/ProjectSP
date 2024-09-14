// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SPPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSP_API ASPPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASPPlayerController();


	virtual void BeginPlay() override;
protected:

};

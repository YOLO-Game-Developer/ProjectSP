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
	void SetUI(bool InVisible);

	virtual void RestartLevel() override;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Widget)
	TSubclassOf<class UUserWidget> EndedUIClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Widget)
	TObjectPtr<class UUserWidget> EndedUI;


	void InitWidget();
};

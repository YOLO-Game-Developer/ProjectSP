// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/SPAIInterface.h"
#include "SPAISpawner.generated.h"


UCLASS()
class PROJECTSP_API ASPAISpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPAISpawner();

	FOnAIDeathCountChanged OnAIDeathCountChanged;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	UPROPERTY()
	FTimerHandle SpawnTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	TSubclassOf<class ASPCharacterNonPlayer> AIClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float MaxAICount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float MinAICount;

	float AICount;

protected:

	void SpawnAI();

	void ReduceAICount();

};

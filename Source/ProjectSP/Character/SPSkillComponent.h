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

	USPSkillComponent(const FObjectInitializer& ObjectInitializer);

	void Attack(); //어차피 공격을 늘리더라도 나중에 늘릴 예정

	void DisplayAttackRange();

	virtual void BeginPlay() override;

protected:

	void CheckAttackCollision();
	bool IsHitByAttack(AActor* CurrentActor, AActor *OtherActor);

protected:

	void DrawDebugCircleArcFanWithDirection(UWorld* World, FVector Center, FVector Direction, float Radius, float StartAngle, float EndAngle, int32 Segments, FColor Color, float Thickness = 1.0f, bool bPersistentLines = false, float LifeTime = -1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Decal")
	TSubclassOf<class AActor> SkillDecalClass;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	TObjectPtr<class AActor> SkillDecalActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	TObjectPtr<class UAnimMontage> SkillMontage;

private:

	float MinDegree;
	float MaxDegree;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/SPGetStatInterface.h"
#include "SPCharacterBase.generated.h"

UCLASS()
class PROJECTSP_API ASPCharacterBase : public ACharacter , public ISPGetStatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASPCharacterBase();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual class USPStatComponent* GetStat();
	bool IsPlayMontage(class UAnimMontage* InMontage);

	virtual void Dead();
	FORCEINLINE void SetDead(bool InDead) { this->bIsDead = InDead; }
	FORCEINLINE bool GetDead() { return bIsDead; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USPStatComponent> Stat;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USPSkillComponent> Skill;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<class UAnimMontage> DeathMontage;
protected:

	uint8 bIsAttacking : 1;

	uint8 bIsDead : 1;
};

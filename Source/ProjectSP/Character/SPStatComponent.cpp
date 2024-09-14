// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SPStatComponent.h"

USPStatComponent::USPStatComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer),MaxHP(100.f), MaxAttack(30.f), HP(0.f), Attack(0.f), RadiusOfAttack(0.f)
{

}

void USPStatComponent::InitStat(float InHP, float InAttack, float InRadiusOfAttack)
{
	HP = InHP;
	Attack = InAttack;
	RadiusOfAttack = InRadiusOfAttack;
}

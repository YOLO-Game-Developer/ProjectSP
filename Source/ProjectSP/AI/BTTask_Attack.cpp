// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Attack.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interfaces/SPAIInterface.h"
EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	/*
	공격을 구현한다.
	*/
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	ISPAIInterface* AIPawn = Cast<ISPAIInterface>(ControllingPawn);
	if (nullptr == AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	FAICharacterAttackFinished OnAttackFinished;
	BTComp = &OwnerComp;
	OnAttackFinished.BindUObject(this, &UBTTask_Attack::OnMontageAttackEnded);

	AIPawn->SetAIAttackDelegate(OnAttackFinished);
	AIPawn->AttackByAI();
	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::OnMontageAttackEnded()
{
	if (BTComp)
	{
		FinishLatentTask(*BTComp, EBTNodeResult::Succeeded);
	}
}


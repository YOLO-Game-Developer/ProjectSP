// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SPAIController.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/SPCharacterNonPlayer.h"
#include "Character/SPStatComponent.h"

ASPAIController::ASPAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BlackboardDataRef(TEXT("/Script/AIModule.BlackboardData'/Game/AI/Blackborads/BB_Default.BB_Default'"));

	if (BlackboardDataRef.Object)
	{
		BBAsset = BlackboardDataRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeRef(TEXT("/Script/AIModule.BehaviorTree'/Game/AI/BehaviorTree/BT_Default.BT_Default'"));

	if (BehaviorTreeRef.Object)
	{
		BTAsset = BehaviorTreeRef.Object;
	}
}

void ASPAIController::RunAI()
{
	UBlackboardComponent* BCPtr = Blackboard.Get();

	FTimerHandle WaitTimer;
	if (UseBlackboard(BBAsset, BCPtr)) //BBAsset�� ����� ������ Blackboard ����
	{
		Blackboard->SetValueAsVector(TEXT("HomePosition"), GetPawn()->GetActorLocation());
		bool RunResult = RunBehaviorTree(BTAsset); //���� Blackboard�� BehaviorTree�� �����ϵ��� ��.
		ensure(RunResult);
	}
}

void ASPAIController::StopAI()
{
	UBehaviorTreeComponent* BTCPtr = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTCPtr)
	{
		BTCPtr->StopTree();
	}
}

void ASPAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
}


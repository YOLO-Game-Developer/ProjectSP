// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/SPAISpawner.h"
#include "Character/SPCharacterNonPlayer.h"
// Sets default values
ASPAISpawner::ASPAISpawner() : MaxAICount(3), AICount(0)
{
	OnAIDeathCountChanged.BindUObject(this, &ASPAISpawner::ReduceAICount);
}

// Called when the game starts or when spawned
void ASPAISpawner::BeginPlay()
{
	Super::BeginPlay();
	
	//�ʹݿ� 3���� ����
	//�Ѹ��� ������ 1���� ����
	//3���� ������ 3���� ���� 
	SpawnAI();
}

void ASPAISpawner::SpawnAI()
{

	for (int i = 0; i < MaxAICount; i++)
	{
		//AI�� �����Ѵ�
		ASPCharacterNonPlayer* NonPlayer = GetWorld()->SpawnActor<ASPCharacterNonPlayer>(AIClass, GetActorTransform());
		NonPlayer->InitSpawn(OnAIDeathCountChanged);

		AICount++;
	}

}

void ASPAISpawner::ReduceAICount()
{
	UE_LOG(LogTemp, Log, TEXT("Reduce Current AI Count %lf"), AICount);
	AICount--;
	//���� ������ �Ѹ����� ����
	ASPCharacterNonPlayer* NonPlayer = GetWorld()->SpawnActor<ASPCharacterNonPlayer>(AIClass, GetActorTransform());
	NonPlayer->InitSpawn(OnAIDeathCountChanged);
}

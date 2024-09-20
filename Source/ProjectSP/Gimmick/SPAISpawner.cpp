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
	
	//초반에 3마리 생성
	//한마리 죽으면 1마리 생성
	//3마리 죽으면 3마리 생성 
	SpawnAI();
}

void ASPAISpawner::SpawnAI()
{

	for (int i = 0; i < MaxAICount; i++)
	{
		//AI를 스폰한다
		ASPCharacterNonPlayer* NonPlayer = GetWorld()->SpawnActor<ASPCharacterNonPlayer>(AIClass, GetActorTransform());
		NonPlayer->InitSpawn(OnAIDeathCountChanged);

		AICount++;
	}

}

void ASPAISpawner::ReduceAICount()
{
	UE_LOG(LogTemp, Log, TEXT("Reduce Current AI Count %lf"), AICount);
	AICount--;
	//죽을 때마다 한마리씩 스폰
	ASPCharacterNonPlayer* NonPlayer = GetWorld()->SpawnActor<ASPCharacterNonPlayer>(AIClass, GetActorTransform());
	NonPlayer->InitSpawn(OnAIDeathCountChanged);
}

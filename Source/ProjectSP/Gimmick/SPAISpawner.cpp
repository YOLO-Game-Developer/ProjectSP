// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/SPAISpawner.h"
#include "Character/SPCharacterNonPlayer.h"
// Sets default values
ASPAISpawner::ASPAISpawner() : MaxAICount(5), MinAICount(2), AICount(0)
{
	OnAIDeathCountChanged.BindUObject(this, &ASPAISpawner::ReduceAICount);
}

// Called when the game starts or when spawned
void ASPAISpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(SpawnTimer,this, &ASPAISpawner::SpawnAI, 10.f,true);
}

void ASPAISpawner::SpawnAI()
{
	if (AICount > MaxAICount)
	{
		return; //더이상 생성하지 않는다.
	}

	if (AICount < MinAICount)
	{
		for (int i = AICount; i <= MinAICount; i++)
		{
			//AI를 스폰한다
			ASPCharacterNonPlayer* NonPlayer = GetWorld()->SpawnActorDeferred<ASPCharacterNonPlayer>(AIClass, GetActorTransform());

			if (NonPlayer)
			{
				NonPlayer->FinishSpawning(GetActorTransform());
				NonPlayer->InitSpawn(OnAIDeathCountChanged);
			}

			AICount++;
		}

		UE_LOG(LogTemp, Log, TEXT("Increase Current AI Count %lf"), AICount);
		return;
	}

	ASPCharacterNonPlayer* NonPlayer = GetWorld()->SpawnActorDeferred<ASPCharacterNonPlayer>(AIClass, GetActorTransform());

	if (NonPlayer)
	{
		NonPlayer->FinishSpawning(GetActorTransform());
	}

	UE_LOG(LogTemp, Log, TEXT("Increase Current AI Count %lf"), AICount);
	AICount++;
}

void ASPAISpawner::ReduceAICount()
{
	UE_LOG(LogTemp, Log, TEXT("Reduce Current AI Count %lf"), AICount);
	AICount--;
}

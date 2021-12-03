// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPrepAttackState.h"

#include "SideScroller/EnemySoldier.h"

EnemyPrepAttackState::EnemyPrepAttackState()
{
	attackTimer = 0;
	pauseTime = 0;
}

EnemyPrepAttackState::~EnemyPrepAttackState()
{
}

void EnemyPrepAttackState::StateBegin(AEnemySoldier* _myEnemy, FVector* _playerLoc, float _pauseTime)
{
	myEnemy = _myEnemy;
	playerLoc = _playerLoc;
	pauseTime = _pauseTime;
	attackHeight = FMath::RandBool();
}

void EnemyPrepAttackState::StateTick(float elapsedTime)
{
	attackTimer += elapsedTime;
	bool dir = (playerLoc->X - myEnemy->GetActorLocation().X) <= 0;
	myEnemy->direction = dir;
	myEnemy->Animate(2+attackHeight);
	if(attackTimer > pauseTime)
	{
		myEnemy->LaunchAttack(attackHeight);
		attackTimer = 0;
		attackHeight = FMath::RandBool();
	}
}

char EnemyPrepAttackState::TakeDamage(char damage)
{
	return 0;
}

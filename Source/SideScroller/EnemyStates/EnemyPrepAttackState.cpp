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
}

void EnemyPrepAttackState::StateTick(float elapsedTime)
{
	attackTimer += elapsedTime;
	const bool timerDone = attackTimer > pauseTime;
	myEnemy->ManageStates(1 + (timerDone));

	attackTimer *= !timerDone;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAttackState.h"

#include "EnemySoldier.h"

EnemyAttackState::EnemyAttackState()
{
	attackTimer = 0.5f;
}

EnemyAttackState::~EnemyAttackState()
{
	
}

void EnemyAttackState::StateBegin(AEnemySoldier* _myEnemy, FVector* _playerLoc)
{
	myEnemy = _myEnemy;
	playerLoc = _playerLoc;
}

void EnemyAttackState::StateTick(float elapsedTime)
{
	attackTimer -= elapsedTime;
	bool endState = attackTimer < 0.0f;
	myEnemy->ManageStates(!endState * 3);
	attackTimer = !endState * attackTimer + endState * 0.5f;
}

char EnemyAttackState::TakeDamage(char damage)
{
	const bool damaged = damage > 0;
	myEnemy->ManageStates(damaged*1 + !damaged*3);
	attackTimer = damaged * 0.5f + !damaged * attackTimer;
	return  damage;
}


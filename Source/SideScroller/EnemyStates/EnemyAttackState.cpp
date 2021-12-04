// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAttackState.h"

#include "SideScroller/EnemySoldier.h"

EnemyAttackState::EnemyAttackState()
{
	attackTimer = 0.5f;
	overSwing = 0.5f;
}

EnemyAttackState::~EnemyAttackState()
{
	
}

void EnemyAttackState::StateBegin(AEnemySoldier* _myEnemy, FVector* _playerLoc, float _overSwing)
{
	overSwing = _overSwing;
	myEnemy = _myEnemy;
	playerLoc = _playerLoc;
	attackTimer = overSwing;
}

void EnemyAttackState::StateTick(float elapsedTime)
{
	attackTimer -= elapsedTime;
	bool endState = attackTimer < 0.0f;
	myEnemy->ManageStates(!endState * 3);
	attackTimer = !endState * attackTimer + endState * overSwing;
}

char EnemyAttackState::TakeDamage(char damage)
{
	const bool damaged = damage > 0;
	myEnemy->ManageStates(damaged*1 + !damaged*3);
	attackTimer = damaged * 0.5f + !damaged * attackTimer;
	const float location = myEnemy->GetActorLocation().X;
	float dir = MyUtils::Sign(location - playerLoc->X);
	myEnemy->vel.X = 2.75f * dir * damaged + myEnemy->vel.X * !damaged;
	myEnemy->vel.Y = 3.5f * damaged + myEnemy->vel.Y * !damaged;
	return  damage;
}
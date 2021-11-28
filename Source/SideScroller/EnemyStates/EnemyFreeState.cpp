// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFreeState.h"



EnemyFreeState::EnemyFreeState()
{
	BehaviourFncs[0] = &EnemyFreeState::Chase;
	BehaviourFncs[1] = &EnemyFreeState::Flee;
}

EnemyFreeState::~EnemyFreeState()
{
}

void EnemyFreeState::StateBegin(AEnemySoldier* _myEnemy, FVector* _playerLoc)
{
	myEnemy = _myEnemy;
	playerLoc = _playerLoc;
}

void EnemyFreeState::StateTick(float ElapsedTime)
{
	
}

void EnemyFreeState::Chase()
{
	float speed = playerLoc->X - myEnemy->GetActorLocation().X;
	speed = 5 * MyUtils::Sign(speed);
	myEnemy->vel.X = speed;
	//myEnemy->ManageStates(abs(speed) < 0.5f);
}

void EnemyFreeState::Flee()
{
	float distance = myEnemy->GetActorLocation().X - playerLoc->X;
	float speed = 5 * MyUtils::Sign(distance);
	myEnemy->vel.X = speed * (1 - 2*(distance < 1.0f));
}

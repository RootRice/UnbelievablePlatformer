// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyRecoilState.h"

#include "SideScroller/EnemySoldier.h"

EnemyRecoilState::EnemyRecoilState()
{
	timer = 0;
}

EnemyRecoilState::~EnemyRecoilState()
{
}

void EnemyRecoilState::StateBegin(AEnemySoldier* _myEnemy, FVector* _playerLoc)
{
	myEnemy = _myEnemy;
	playerLoc = _playerLoc;
}

void EnemyRecoilState::StateTick(float elapsedTime)
{
	timer += elapsedTime;
	const bool timerUp = timer > 3.0f;
	bool playerAttackable = (playerLoc->X - myEnemy->GetActorLocation().X < 200.0f);
	bool nextState = !timerUp;
	
	myEnemy->ManageStates(timerUp * (playerAttackable * 2) + nextState);
	myEnemy->Animate(1);
	timer *= !timerUp;
}

char EnemyRecoilState::TakeDamage(char Damage)
{
	return 0;
}

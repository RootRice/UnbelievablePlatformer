// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFreeState.h"



EnemyFreeState::EnemyFreeState()
{
	currentBehaviour = 0;
	attackTimer = 0;
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

	
void EnemyFreeState::StateBegin(AEnemySoldier* _myEnemy, FVector* _playerLoc, float _leftBounds, float _rightBounds)
{
	myEnemy = _myEnemy;
	playerLoc = _playerLoc;
	leftBounds = _leftBounds;
	rightBounds = _rightBounds;
}

void EnemyFreeState::StateTick(float elapsedTime)
{
	attackTimer -= elapsedTime;
	currentBehaviour = attackTimer < 0.0f;
	(this->*BehaviourFncs[currentBehaviour])();
}

void EnemyFreeState::TakeDamage()
{
	const float location = myEnemy->GetActorLocation().X;
	float dir = MyUtils::Sign(location - playerLoc->X);
	myEnemy->vel.X = 7 * dir;
	myEnemy->vel.Y = 13;
}

void EnemyFreeState::Chase()
{
	
	const float location = myEnemy->GetActorLocation().X;
	float speed = playerLoc->X - location;
	speed = 5 * MyUtils::Sign(speed);
	
	bool dir = speed <= 0;
	
	speed *= ((location + speed) < rightBounds) && ((location + speed) > leftBounds);
	myEnemy->vel.X = speed;

	myEnemy->direction = dir;
}

void EnemyFreeState::Flee()
{

	const float location = myEnemy->GetActorLocation().X;
	float speed = location - playerLoc->X;
	speed = 5 * MyUtils::Sign(speed);
	
	bool dir = speed <= 0;
	
	speed *= ((location + speed) < rightBounds) & ((location + speed) > leftBounds);
	myEnemy->vel.X = speed;

	myEnemy->direction = dir;
	//UE_LOG(LogTemp, Warning, TEXT("FLEEING %F"), speed);
}

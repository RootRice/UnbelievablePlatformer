// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFreeState.h"



EnemyFreeState::EnemyFreeState()
{
	currentBehaviour = 0;
	attackTimer = 2;
	BehaviourFncs[0] = &EnemyFreeState::Flee;
	BehaviourFncs[1] = &EnemyFreeState::Chase;
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
	myEnemy->Animate(0);
}

char EnemyFreeState::TakeDamage(char damage)
{
	bool damaged = damage > 0;
	const float location = myEnemy->GetActorLocation().X;
	float dir = MyUtils::Sign(location - playerLoc->X);
	myEnemy->vel.X = 2.75f * dir * damaged + myEnemy->vel.X * !damaged;
	myEnemy->vel.Y = 3.5f * damaged + myEnemy->vel.Y * !damaged;
	myEnemy->ManageStates(damaged);
	return damage;
}

void EnemyFreeState::Chase()
{
	const float location = myEnemy->GetActorLocation().X;
	float speed = playerLoc->X - location;
	const bool shouldAttack = abs(speed) < 200;
	myEnemy->ManageStates( shouldAttack* 2);
	attackTimer = shouldAttack *2;
	speed = 1.7f * MyUtils::Sign(speed);
	
	bool dir = speed <= 0;
	
	speed *= CalculateBounds(dir, location + speed);//((location + speed) < rightBounds) && ((location + speed) > leftBounds);
	myEnemy->vel.X = speed;

	myEnemy->direction = dir;
}

void EnemyFreeState::Flee()
{

	const float location = myEnemy->GetActorLocation().X;
	float speed = location - playerLoc->X;
	speed = 1.7f * MyUtils::Sign(speed);
	
	bool dir = speed <= 0;
	
	speed *= CalculateBounds(dir, location + speed);//((location + speed) < rightBounds) & ((location + speed) > leftBounds);
	myEnemy->vel.X = speed;

	myEnemy->direction = dir;
	//UE_LOG(LogTemp, Warning, TEXT("FLEEING %F"), speed);
}

bool inline EnemyFreeState::CalculateBounds(bool dir, float newLoc)
{
	bool leftBound = (newLoc > leftBounds) | !dir;
	bool rightBound	 = (newLoc < rightBounds) | dir;
	return leftBound & rightBound;
}

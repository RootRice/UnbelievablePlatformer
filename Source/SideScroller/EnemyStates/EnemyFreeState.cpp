// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFreeState.h"



EnemyFreeState::EnemyFreeState()
{
<<<<<<< Updated upstream
=======
	currentBehaviour = 0;
	attackTimer = 0;
>>>>>>> Stashed changes
	BehaviourFncs[0] = &EnemyFreeState::Chase;
	BehaviourFncs[1] = &EnemyFreeState::Flee;
}

EnemyFreeState::~EnemyFreeState()
{
}

<<<<<<< Updated upstream
void EnemyFreeState::StateBegin(AEnemySoldier* _myEnemy, FVector* _playerLoc)
{
	myEnemy = _myEnemy;
	playerLoc = _playerLoc;
}

void EnemyFreeState::StateTick(float ElapsedTime)
{
	
=======
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
>>>>>>> Stashed changes
}

void EnemyFreeState::Chase()
{
<<<<<<< Updated upstream
	float speed = playerLoc->X - myEnemy->GetActorLocation().X;
	speed = 5 * MyUtils::Sign(speed);
	myEnemy->vel.X = speed;
	//myEnemy->ManageStates(abs(speed) < 0.5f);
=======
	const float location = myEnemy->GetActorLocation().X;
	float speed = playerLoc->X - location;
	speed = 5 * MyUtils::Sign(speed);
	
	bool dir = speed <= 0;
	
	speed *= ((location + speed) < rightBounds) && ((location + speed) > leftBounds);
	myEnemy->vel.X = speed;

	myEnemy->direction = dir;
>>>>>>> Stashed changes
}

void EnemyFreeState::Flee()
{
<<<<<<< Updated upstream
	float distance = myEnemy->GetActorLocation().X - playerLoc->X;
	float speed = 5 * MyUtils::Sign(distance);
	myEnemy->vel.X = speed * (1 - 2*(distance < 1.0f));
=======
	const float location = myEnemy->GetActorLocation().X;
	float speed = location - playerLoc->X;
	speed = 5 * MyUtils::Sign(speed);
	
	bool dir = speed <= 0;
	
	speed *= ((location + speed) < rightBounds) & ((location + speed) > leftBounds);
	myEnemy->vel.X = speed;

	myEnemy->direction = dir;
	//UE_LOG(LogTemp, Warning, TEXT("FLEEING %F"), speed);
>>>>>>> Stashed changes
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class AEnemySoldier;
/**
 * 
 */
class SIDESCROLLER_API EnemyBaseState
{
public:
	EnemyBaseState();
	virtual ~EnemyBaseState();

	virtual void StateBegin();
	virtual void StateBegin(AEnemySoldier* _myEnemy);
	virtual void StateBegin(AEnemySoldier* _myEnemy, FVector* _playerLoc);
	virtual void StateBegin(AEnemySoldier* _myEnemy, FVector* _playerLoc, float _duration);
	virtual void StateBegin(AEnemySoldier* _myEnemy, FVector* _playerLoc, float leftBounds, float rightBounds);
	virtual void StateTick(float elapsedTime);

	virtual char TakeDamage(char damage);
	
protected:
	AEnemySoldier* myEnemy;
	FVector* playerLoc;
	
};

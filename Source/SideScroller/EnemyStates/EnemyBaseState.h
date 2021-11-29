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
	virtual void StateBegin(AEnemySoldier* _myEnemy, FVector* _playerLoc);
<<<<<<< Updated upstream
=======
	virtual void StateBegin(AEnemySoldier* _myEnemy, FVector* _playerLoc, float leftBounds, float rightBounds);
>>>>>>> Stashed changes
	virtual void StateTick(float elapsedTime);
protected:
	AEnemySoldier* myEnemy;
	FVector* playerLoc;
	
};

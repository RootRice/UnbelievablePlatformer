// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SideScroller/EnemySoldier.h"
#include "EnemyBaseState.h"

/**
 * 
 */
class SIDESCROLLER_API EnemyFreeState : public EnemyBaseState
{
public:
	EnemyFreeState();
	~EnemyFreeState();

<<<<<<< Updated upstream
	virtual void StateBegin(AEnemySoldier* _myEnemy, FVector* _playerLoc) override;
=======
	virtual void StateBegin(AEnemySoldier* _myEnemy, FVector* _playerLoc, float _leftBounds, float _rightBounds) override;
>>>>>>> Stashed changes
	virtual void StateTick(float elapsedTime) override;

private:
	float attackTimer;
<<<<<<< Updated upstream
=======
	
>>>>>>> Stashed changes
	void (EnemyFreeState::*BehaviourFncs[2])();

	char currentBehaviour;
	void Chase();
	void Flee();
<<<<<<< Updated upstream
=======

	float leftBounds;
	float rightBounds;
>>>>>>> Stashed changes
};

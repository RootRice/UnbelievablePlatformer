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

	virtual void StateBegin(AEnemySoldier* _myEnemy, FVector* _playerLoc) override;
	virtual void StateBegin(AEnemySoldier* _myEnemy, FVector* _playerLoc, float _leftBounds, float _rightBounds) override;
	virtual void StateTick(float elapsedTime) override;

	virtual void TakeDamage() override;

private:
	float attackTimer;
	
	void (EnemyFreeState::*BehaviourFncs[2])();

	char currentBehaviour;
	void Chase();
	void Flee();

	float leftBounds;
	float rightBounds;
};

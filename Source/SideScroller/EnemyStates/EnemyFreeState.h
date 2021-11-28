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
	virtual void StateTick(float elapsedTime) override;

private:
	float attackTimer;
	void (EnemyFreeState::*BehaviourFncs[2])();

	char currentBehaviour;
	void Chase();
	void Flee();
};

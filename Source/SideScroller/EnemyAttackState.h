// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyStates/EnemyBaseState.h"

/**
 * 
 */
class SIDESCROLLER_API EnemyAttackState : public EnemyBaseState
{
public:
	EnemyAttackState();
	~EnemyAttackState();

	virtual void StateBegin(AEnemySoldier* _myEnemy, FVector* _playerLoc) override;
	virtual void StateTick(float elapsedTime) override;

	virtual char TakeDamage(char damage) override;

private:
	float attackTimer;
};

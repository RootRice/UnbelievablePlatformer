// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBaseState.h"

/**
 * 
 */
class SIDESCROLLER_API EnemyPrepAttackState : public EnemyBaseState
{
public:
	EnemyPrepAttackState();
	~EnemyPrepAttackState();
	
	virtual void StateBegin(AEnemySoldier* _myEnemy, FVector* _playerLoc, float _pauseTime) override;
	virtual  void StateTick(float elapsedTime) override;
	virtual  char TakeDamage(char damage) override;
private:
	float attackTimer;
	float pauseTime;
	bool attackHeight;
};

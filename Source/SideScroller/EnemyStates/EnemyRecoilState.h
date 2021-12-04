// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBaseState.h"
#include "SideScroller/MainCharacter.h"

/**
 * 
 */
class SIDESCROLLER_API EnemyRecoilState : public EnemyBaseState
{
public:
	EnemyRecoilState();
	~EnemyRecoilState();

	virtual void StateBegin(AEnemySoldier* _myEnemy, FVector* _playerLoc, float _recoilDuration) override;
	virtual void StateTick(float elapsedTime) override;

	virtual char TakeDamage(char damage) override;

private:
	float timer;
	float recoilDuration;
};

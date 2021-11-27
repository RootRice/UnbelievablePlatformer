// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttackingState.h"

#include "CollisionUtils.h"
#include "MainCharacter.h"

PlayerAttackingState::PlayerAttackingState()
{
	attackIndex = 0;
	attackTimer = 0;
	queuedState = 0;
	queuedDirection = 0;
	InputFncs[0] = &PlayerAttackingState::ChangeDir;
	InputFncs[1] = &PlayerAttackingState::NullAction;
	InputFncs[2] = &PlayerAttackingState::QueueAttack;
}

PlayerAttackingState::~PlayerAttackingState()
{
}
void PlayerAttackingState::StateBegin(AMainCharacter* _myCharacter, FVector* _vel)
{
	vel = _vel;
	myCharacter = _myCharacter;
	direction = MyUtils::Sign(vel->X);
	queuedDirection = direction;
}

void PlayerAttackingState::StateBegin(AMainCharacter* _myCharacter, FVector* _pos, FVector* _vel)
{
	position = _pos;
	vel = _vel;
	myCharacter = _myCharacter;
}

void PlayerAttackingState::StateTick(float ElapsedTime)
{
	vel->X = attackMomentum[attackIndex] *direction;
	
	attackTimer += ElapsedTime;
	if(attackTimer > attackTiming[attackIndex])
	{
		attackIndex = MyUtils::LoopIndex(attackIndex+1, 3);
		ProcessQueue();
	}
	Animate();
}

void PlayerAttackingState::StateInput(char Input, float Value)
{
	(this->*InputFncs[Input])(Value);
}

void PlayerAttackingState::Animate()
{
	char animation = attackIndex + 2;
	myCharacter->SetAnimation(animation);
}

void PlayerAttackingState::ChangeDir(float Value)
{
	const bool Switch = abs(Value) > 0;
	queuedDirection = MyUtils::Sign(Value) * Switch + queuedDirection * !Switch;
}

void PlayerAttackingState::NullAction(float Value)
{
	
}

void PlayerAttackingState::QueueAttack(float Value)
{
	const bool shouldQueue = attackTimer > 0.25f;
	queuedState = 1 * shouldQueue + queuedState * !shouldQueue;
}

void inline PlayerAttackingState::ProcessQueue()
{
	attackTimer = 0;
	myCharacter->ManageState(queuedState);
	direction = queuedDirection;
	myCharacter->direction = direction > 0;
	queuedState = 0;
	
}
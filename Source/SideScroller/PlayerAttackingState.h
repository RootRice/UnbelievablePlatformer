// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseState.h"

/**
 * 
 */
class SIDESCROLLER_API PlayerAttackingState : public PlayerBaseState
{
public:
	PlayerAttackingState();
	~PlayerAttackingState();
	
	virtual void StateBegin(AMainCharacter* _myCharacter, FVector* _vel) override;
	virtual void StateBegin(AMainCharacter* _myCharacter,FVector* _pos, FVector* _vel) override;
	virtual void StateTick(float elapsedTime) override;
	virtual void StateInput(char input, float Value) override;
	virtual void Animate() override;
	virtual char TakeDamage(char damage) override;
private:
	void (PlayerAttackingState::*InputFncs[4])(float);
	void ChangeDir(float Value);
	void NullAction(float Value);
	void QueueAttack(float Value);
	void Crouch(float Value);
	void Attack();

	FVector* position;
	FVector* vel;
	
	FVector2D attackSize[3] = {FVector2D(100,50), FVector2D(100,50), FVector2D(100,50)};
	float attackMomentum[3] = {0.25f, 0.55f, 0.35f};
	char direction;
	float attackTiming[3] = {0.5f, 0.5f, 0.5f};
	char attackIndex;
	float attackTimer;

	void ProcessQueue();
	char queuedState;
	char queuedDirection;
};

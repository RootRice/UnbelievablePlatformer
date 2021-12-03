// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseState.h"
#include "MyUtils.h"

/**
 * 
 */
class SIDESCROLLER_API PlayerCrouchState : public PlayerBaseState
{
public:
	PlayerCrouchState();
	~PlayerCrouchState();

	virtual void StateBegin(AMainCharacter* _myCharacter, FVector* _vel) override;
	virtual void StateTick(float elapsedTime) override;
	virtual void StateInput(char input, float Value) override;
	virtual  void Animate() override;
	virtual char TakeDamage(char damage) override;

private:
	FVector* vel;
	void Move(float Value);
	void Jump(float Value);
	void Attack(float Value);
	void Crouch(float Value);
	void NullAction(float Value);
	void (PlayerCrouchState::*InputFncs[4])(float);
	float timer;
};

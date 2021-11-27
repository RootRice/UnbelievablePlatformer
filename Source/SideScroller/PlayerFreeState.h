// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseState.h"
/**
 * 
 */
class SIDESCROLLER_API PlayerFreeState : public PlayerBaseState
{
public:
	PlayerFreeState();
	~PlayerFreeState() override;

	virtual void StateBegin(AMainCharacter* _myCharacter, FVector* _vel) override;
	virtual void StateTick(float elapsedTime) override;
	virtual void StateInput(char input, float Value) override;
	virtual  void Animate() override;

private:
	FVector* vel;
	void Move(float Value);
	void Jump(float Value);
	void Attack(float Value);
	void NullAction(float Value);
	void (PlayerFreeState::*InputFncs[3])(float);
	

	

};
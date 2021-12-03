// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerBaseState.h"
#include "CoreMinimal.h"

/**
 * 
 */
class SIDESCROLLER_API PlayerDamagedState : public PlayerBaseState
{
public:
	PlayerDamagedState();
	~PlayerDamagedState();

	virtual void StateBegin(AMainCharacter* _myCharacter, FVector* _vel) override;
	virtual void StateTick(float elapsedTime) override;
	virtual void StateInput(char input, float Value) override;
	virtual  void Animate() override;
	virtual char TakeDamage(char damage) override;

private:
	float timer;
};

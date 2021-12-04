// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDamagedState.h"

#include "MainCharacter.h"

PlayerDamagedState::PlayerDamagedState()
{
	timer = 0;
}

PlayerDamagedState::~PlayerDamagedState()
{
}

void PlayerDamagedState::StateBegin(AMainCharacter* mainCharacter, FVector* _pos)
{
	myCharacter = mainCharacter;
}

void PlayerDamagedState::StateTick(float elapsedTime)
{
	timer += elapsedTime;
	const bool timerUp = timer < 0.5f;
	myCharacter->ManageState(timerUp * 3);
	myCharacter->SetAnimation(0);
	timer *= timerUp;
}

void PlayerDamagedState::StateInput(char input, float value)
{
	
}

void PlayerDamagedState::Animate()
{
	
}

char PlayerDamagedState::TakeDamage(char damage)
{
	return 0;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCrouchState.h"

#include "MainCharacter.h"

PlayerCrouchState::PlayerCrouchState()
{
	timer = 0;
	InputFncs[0] = &PlayerCrouchState::Move;
	InputFncs[1] = &PlayerCrouchState::Jump;
	InputFncs[2] = &PlayerCrouchState::Attack;
	InputFncs[3] = &PlayerCrouchState::Crouch;
}

PlayerCrouchState::~PlayerCrouchState()
{
}

void PlayerCrouchState::StateBegin(AMainCharacter* _myCharacter, FVector* _vel)
{
	myCharacter = _myCharacter;
	vel = _vel;
}

void PlayerCrouchState::StateTick(float elapsedTime)
{
	timer +=elapsedTime;
}

void PlayerCrouchState::StateInput(char input, float Value)
{
	input = MyUtils::Min(input, 4);
	(this->*InputFncs[input])(Value);
}

void PlayerCrouchState::Animate()
{
	myCharacter->SetAnimation(2);
}

char PlayerCrouchState::TakeDamage(char damage)
{
	const bool damaged = damage != 0;
	myCharacter->ManageState(3* damaged + 1 * !damaged);
	return damage;
}

void PlayerCrouchState::Move(float Value)
{
	const bool shouldMove = (Value != 0) && (timer > 0.25f);
	myCharacter->ManageState(!shouldMove);
	myCharacter->crouched = !shouldMove;
	timer *= !shouldMove;
	Animate();
}

void PlayerCrouchState::Jump(float Value)
{
	const bool shouldMove = (Value != 0) && (timer > 0.25f);
	myCharacter->ManageState(!shouldMove);
	vel->Z += Value;
	myCharacter->crouched = !shouldMove;
	timer *= !shouldMove;
}

void PlayerCrouchState::Attack(float Value)
{
	myCharacter->ManageState(2);
	myCharacter->crouched = false;
	timer = 0;
}

void PlayerCrouchState::Crouch(float Value)
{
	
}

void PlayerCrouchState::NullAction(float Value)
{
	
}

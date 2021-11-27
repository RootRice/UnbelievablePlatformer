// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFreeState.h"

#include "MainCharacter.h"
#include "MyUtils.h"


PlayerFreeState::PlayerFreeState()
{
	InputFncs[0] = &PlayerFreeState::Move;
	InputFncs[1] = &PlayerFreeState::Jump;
	InputFncs[2] = &PlayerFreeState::Attack;
	InputFncs[3] = &PlayerFreeState::Crouch;
}

PlayerFreeState::~PlayerFreeState()
{
}

void PlayerFreeState::StateBegin(AMainCharacter* _myCharacter, FVector* _vel)
{
	myCharacter = _myCharacter;
	vel = _vel;
}

void PlayerFreeState::StateTick(float elapsedTime)
{
	Animate();
}

void PlayerFreeState::StateInput(char input, float Value)
{
	input = MyUtils::Min(input, 4);
	(this->*InputFncs[input])(Value);
}

void PlayerFreeState::Animate()
{
	const bool crouched = myCharacter->crouched;
	char animation = abs(vel->X) > 0;
	animation = animation * !crouched + 2 * crouched;
	myCharacter->SetAnimation(animation);
}

void PlayerFreeState::Move(float Value)
{
	vel->X = Value;
	const bool moving = Value != 0;
	myCharacter->direction = (myCharacter->direction & !moving) | ((MyUtils::Sign(Value) > 0) & moving);
	if(Value != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Discrepancy: %f, %f"), Value);
	}
	
}

void PlayerFreeState::Jump(float Value)
{
	vel->Z += Value;
}

void PlayerFreeState::Attack(float Value)
{
	myCharacter->ManageState(2*myCharacter->grounded);
}

void PlayerFreeState::Crouch(float Value)
{
	const bool shouldCrouch = Value == 1;
	myCharacter->crouched = shouldCrouch;
	vel->X = vel->X * !shouldCrouch;
	myCharacter->ManageState(shouldCrouch*1);
}

void PlayerFreeState::NullAction(float Value)
{
	
}

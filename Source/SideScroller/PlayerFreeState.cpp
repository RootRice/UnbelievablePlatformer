// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFreeState.h"

#include "MainCharacter.h"
#include "MyUtils.h"


PlayerFreeState::PlayerFreeState()
{
	InputFncs[0] = &PlayerFreeState::Move;
	InputFncs[1] = &PlayerFreeState::Jump;
	InputFncs[2] = &PlayerFreeState::Attack;
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
	input = MyUtils::Min(input, 3);
	(this->*InputFncs[input])(Value);
}

void PlayerFreeState::Animate()
{
	char animation = abs(vel->X) > 0;
	UE_LOG(LogTemp, Warning, TEXT("ANIMATION IS %i"), abs(vel->X));
	myCharacter->SetAnimation(animation);
}

void PlayerFreeState::Move(float Value)
{
	vel->X = Value;
	const bool moving = Value != 0;
	myCharacter->direction = (myCharacter->direction & !moving) | ((MyUtils::Sign(Value) > 0) & moving);
}

void PlayerFreeState::Jump(float Value)
{
	vel->Z += Value;
}

void PlayerFreeState::Attack(float Value)
{
	myCharacter->ManageState(1);
	UE_LOG(LogTemp, Warning, TEXT("STATE IS 1"));
}

void PlayerFreeState::NullAction(float Value)
{
	
}

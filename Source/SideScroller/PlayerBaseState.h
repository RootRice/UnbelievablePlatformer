// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"

class AMainCharacter;
/**
 * 
 */
class SIDESCROLLER_API PlayerBaseState
{
public:
	PlayerBaseState();
	virtual ~PlayerBaseState();
	
	virtual void StateBegin(AMainCharacter* _myCharacter);
	virtual void StateBegin(AMainCharacter* _myCharacter, FVector* _vel);
	virtual void StateBegin(AMainCharacter* _myCharacter, FVector* _pos, FVector* _vel);
	virtual void StateTick(float elapsedTime);
	virtual void StateInput(char input, float Value);
	virtual void Animate();
protected:
	AMainCharacter* myCharacter;
};

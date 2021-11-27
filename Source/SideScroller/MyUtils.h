// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
static class SIDESCROLLER_API MyUtils
{
public:
	MyUtils();
	~MyUtils();

	static float Max(float x, float y);
	static float Min(float x, float y);
	static int Sign(float x);
	static unsigned int LoopIndex(unsigned int index, unsigned int loopPoint);
};

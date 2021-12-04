// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SIDESCROLLER_API MyUtils
{
public:
	MyUtils();
	~MyUtils();

	static float Max(float x, float y)
	{
		return (x > y) * x + (x < y) * y;
	}
	static float Min(float x, float y)
	{
		return (x < y) * x + (x > y) * y;
	}
	static int Sign(float x)
	{
		return (x > 0) - (x < 0);
	}
	
	static unsigned int LoopIndex(unsigned int index, unsigned int loopPoint)
	{
		return index % loopPoint;
	}
};

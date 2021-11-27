// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUtils.h"

MyUtils::MyUtils()
{
}

MyUtils::~MyUtils()
{
}

inline float MyUtils::Max(float x, float y)
{
	return (x > y) * x + (x < y) * y;
}

inline float MyUtils::Min(float x, float y)
{
	return (x < y) * x + (x > y) * y;
}

inline int MyUtils::Sign(float x)
{
	return (x > 0) - (x < 0);
}

inline unsigned int MyUtils::LoopIndex(unsigned int index, unsigned int loopPoint)
{
	return index % loopPoint;
}

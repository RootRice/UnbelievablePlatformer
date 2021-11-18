// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
static class SIDESCROLLER_API MyUtils : UObject
{
public:
	MyUtils();
	~MyUtils();

	static float Max(float x, float y);
	static char Sign(float x);
};

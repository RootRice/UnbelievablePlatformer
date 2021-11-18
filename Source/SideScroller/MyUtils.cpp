// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUtils.h"

MyUtils::MyUtils()
{
}

MyUtils::~MyUtils()
{
}

float MyUtils::Max(float x, float y)
{
	return (x > y) * x + (x < y) * y;
}

char MyUtils::Sign(float x)
{
	return (x > 0) - (x < 0);
}

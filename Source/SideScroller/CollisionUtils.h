// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
/**
 * 
 */
static class SIDESCROLLER_API CollisionUtils
{
public:
	CollisionUtils();
	~CollisionUtils();

	static void AddStaticAxisAligned(FVector position, FVector2D size);
	static void AddDynamicAxisAligned(FVector* position, FVector* size);

	static void CheckStaticCollisions(FVector position, FVector2D size);

private:
	static TArray<FVector> staticAAPos;
	static TArray<FVector> staticAASize;
	
	static TArray<FVector*> dynamicAAPos;
	static TArray<FVector*> dynamicAASize;

};

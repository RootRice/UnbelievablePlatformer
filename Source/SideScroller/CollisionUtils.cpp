// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionUtils.h"

CollisionUtils::CollisionUtils()
{
}

CollisionUtils::~CollisionUtils()
{
}

TArray<FVector> CollisionUtils::staticAAPos;
TArray<FVector> CollisionUtils::staticAASize;
TArray<FVector*> CollisionUtils::dynamicAAPos;
TArray<FVector*> CollisionUtils::dynamicAASize;

void CollisionUtils::AddStaticAxisAligned(FVector position, FVector2D size)
{
	staticAAPos.Add(position);
	staticAASize.Add(FVector(size.X, 0.0f, size.Y));
	UE_LOG(LogTemp, Warning, TEXT("Collision"))
}



void CollisionUtils::AddDynamicAxisAligned(FVector* position, FVector* size)
{
	dynamicAAPos.Add(position);
	dynamicAASize.Add(size);
}

void CollisionUtils::CheckStaticCollisions(FVector position, FVector2D _size)
{
	FVector displacement = displacement.ZeroVector;
	const FVector size(_size.X, 0.0f, _size.Y);
	
	const FVector aHalfSize = size/2;
	const FVector aBLC(position - aHalfSize);
	const FVector aTRC(position + aHalfSize);

	FVector bHalfSize;
	FVector bBLC;
	FVector bTRC;

	bool collisionHit;
	
	for(int i = 0; i < staticAAPos.Num(); i++)
	{
		bHalfSize = (staticAASize[i]/2);
		bBLC = staticAAPos[i] - bHalfSize;
		bTRC = staticAAPos[i] + bHalfSize;

		collisionHit = !((bBLC.X > aTRC.X) | (bTRC.X < aBLC.X));
		collisionHit &= !((bBLC.Z > aTRC.Z) | (bTRC.Z < aBLC.Z));
	}
	//UE_LOG(LogTemp, Warning, TEXT("CHARACTER IS AT: %d"), *staticAAPos[0].ToString());
	if(collisionHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Collision"));
	}
	
}


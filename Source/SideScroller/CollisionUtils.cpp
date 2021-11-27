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
TArray<FVector*> CollisionUtils::enemyAAPos;
TArray<FVector> CollisionUtils::enemyAASize;

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

int CollisionUtils::CheckAAStaticCollisions(FVector position, FVector2D _size)
{
	int collisionIndex = 9999;
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
		collisionIndex = collisionHit * i + !collisionHit * 9999;
	}
	//UE_LOG(LogTemp, Warning, TEXT("CHARACTER IS AT: %d"), *staticAAPos[0].ToString());

	return  collisionIndex;
}

FVector CollisionUtils::ResolveAAStaticCollisions(FVector position, FVector2D size, FVector* direction)
{
	FVector displacement = displacement.ZeroVector; //Collision offset accumulator
	bool collisionHit;
	
	const FVector origPos = position;
	const FVector aHalfSize(size.X/2, 0.0f, size.Y/2);
	FVector totalBounds;
	FVector collisionPointMin;
	FVector collisionPointMax;
	FVector surfaceNormal;

	direction->X = (direction->X == 0) * 0.000001f + direction->X;
	direction->Z = (direction->X == 0) * 0.000001f + direction->Z;

	
	
	for(int i = 0;i < staticAAPos.Num(); i++)
	{
		totalBounds = aHalfSize + staticAASize[i]/2;
		collisionPointMin = (staticAAPos[i] - totalBounds - position)/ *direction;
		collisionPointMax = (staticAAPos[i] + totalBounds - position)/ *direction;

		SortVectorComponentsByLength(&collisionPointMin, &collisionPointMax);

		surfaceNormal = FVector((collisionPointMin.X < collisionPointMin.Z), 0.0f, (collisionPointMin.X > collisionPointMin.Z));
		
		collisionHit = !(collisionPointMin.X > collisionPointMax.Z) || (collisionPointMin.Z > collisionPointMax.X);

		float minHit = MyUtils::Max(collisionPointMin.X, collisionPointMin.Z);
		float maxHit = MyUtils::Min(collisionPointMax.X, collisionPointMax.Z);

		collisionHit &= maxHit > 0;
		collisionHit &= minHit < 1;
		displacement = ((minHit * *direction))* collisionHit;

		surfaceNormal = collisionHit * surfaceNormal + surfaceNormal.OneVector * !collisionHit;
		
		*direction = *direction*surfaceNormal*collisionHit + *direction*!collisionHit;
		
		direction->X = (direction->X == 0) * 0.000001f + direction->X;
		direction->Z = (direction->Z == 0) * 0.000001f + direction->Z;

		position = origPos + displacement;
	}
	
	return displacement + *direction;
}

void CollisionUtils::ResolveEnemyHit(FVector position, FVector2D size)
{
	const FVector aHalfSize(size.X/2, 0.0f, size.Y/2);
	const FVector aBLC(position - aHalfSize);
	const FVector aTRC(position + aHalfSize);

	FVector bHalfSize;
	FVector bBLC;
	FVector bTRC;

	bool collisionHit;
	
	for(int i = 0; i < enemyAAPos.Num(); i++)
	{
		bHalfSize = (enemyAASize[i]/2);
		bBLC = *enemyAAPos[i] - bHalfSize;
		bTRC = *enemyAAPos[i] + bHalfSize;

		collisionHit = !((bBLC.X > aTRC.X) | (bTRC.X < aBLC.X));
		collisionHit &= !((bBLC.Z > aTRC.Z) | (bTRC.Z < aBLC.Z));
	}
}

void inline CollisionUtils::SortVectorComponentsByLength(FVector* a, FVector* b)
{
	float aC = a->X;
	float bC = b->X;
	bool isALarger = aC > bC;

	float minComponent = (!isALarger) * aC + (isALarger) * bC;
	float maxComponent = (isALarger) * aC + (!isALarger) * bC;

	a->X = minComponent;
	b->X = maxComponent;
	
	aC = a->Z;
	bC = b->Z;
	isALarger = aC > bC;

	minComponent = (!isALarger) * aC + (isALarger) * bC;
	maxComponent = (isALarger) * aC + (!isALarger) * bC;
	
	a->Z = minComponent;
	b->Z = maxComponent;
}



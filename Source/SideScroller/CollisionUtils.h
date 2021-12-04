// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "MyUtils.h"
class AMainCharacter;
class AEnemySoldier;
/**
 * 
 */
class SIDESCROLLER_API CollisionUtils
{
public:
	CollisionUtils();
	~CollisionUtils();

	static void AddStaticAxisAligned(FVector position, FVector2D size);
	static void AddDynamicAxisAligned(FVector* position, FVector* size);
	static void AddAAEnemy(FVector* position, FVector size, AEnemySoldier* soldier);

	static void SetPlayer(FVector* position, FVector2D* size, AMainCharacter* character);

	static int CheckAAStaticCollisions(FVector position, FVector2D size);
	
	static FVector ResolveAAStaticCollisions(FVector position, FVector2D size, FVector* direction);
	
	static void ResolveEnemyHit(FVector position, FVector2D size, char damage);
	static void ResolvePlayerHit(FVector position, FVector2D size, char damage);

	static bool CheckVictoryBox();
	
	static void Reset();

private:
	static TArray<FVector> staticAAPos;
	static TArray<FVector> staticAASize;
	
	static TArray<FVector*> dynamicAAPos;
	static TArray<FVector*> dynamicAASize;
	
	static TArray<FVector*> enemyAAPos;
	static TArray<FVector> enemyAASize;
	static TArray<AEnemySoldier*> enemyAA;

	static FVector* playerLoc;
	static FVector2D* playerSize;
	static AMainCharacter* player;

	static void SortVectorComponentsByLength(FVector *a, FVector *b);

};

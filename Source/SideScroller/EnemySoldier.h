// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collidable.h"
#include "PaperFlipbookComponent.h"
#include "EnemyStates/EnemyBaseState.h"
#include "EnemyStates/EnemyFreeState.h"
#include "CollisionUtils.h"
#include "EnemySoldier.generated.h"

/**
 * 
 */
UCLASS()
class SIDESCROLLER_API AEnemySoldier : public ACollidable
{
	GENERATED_BODY()
public:
	AEnemySoldier();
	~AEnemySoldier();

	void ManageStates(char newState);
	void TakeDamage(char damage);
	
	FVector vel;

	bool direction;
protected:
	virtual  void BeginPlay() override;
	virtual  void Tick(float DeltaTime) override;

	
	
	UPROPERTY(EditAnywhere)
	float leftBounds;

	UPROPERTY(EditAnywhere)
	float rightBounds;

	UPROPERTY(EditAnywhere)
	UPaperFlipbookComponent* flipBook;
	
	
	
private:
	char currentState;
	EnemyBaseState* states[3];
	void UpdatePosition();
	void ApplyDampenForces(float DeltaTime);

	UPROPERTY(EditAnywhere)
	int health;
	
	UPROPERTY(EditAnywhere)
	float attackCooldown;

	UPROPERTY(EditAnywhere)
	float attackPrepDuration;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collidable.h"
#include "PaperFlipbook.h"
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
	void Animate(char animation);
	void LaunchAttack(bool height);
	
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
	EnemyBaseState* states[4];
	void UpdatePosition();
	void ApplyDampenForces(float DeltaTime);

	bool damageable;
	float invulnTimer;

	UPROPERTY(EditAnywhere)
	int health;
	
	UPROPERTY(EditAnywhere)
	float attackCooldown;

	UPROPERTY(EditAnywhere)
	float attackPrepDuration;

	UPROPERTY(EditAnywhere)
	float invulnDuration;
	
	UPROPERTY(EditAnywhere)
	float overSwing;

	UPROPERTY(EditAnywhere)
	UPaperFlipbook* animations[6];

};

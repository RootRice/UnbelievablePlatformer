// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollisionUtils.h"
#include "Collidable.h"
<<<<<<< Updated upstream
=======
#include "PaperFlipbookComponent.h"
>>>>>>> Stashed changes
#include "EnemyStates/EnemyBaseState.h"
#include "EnemyStates/EnemyFreeState.h"
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
	
	FVector vel;

<<<<<<< Updated upstream
=======
	bool direction;
>>>>>>> Stashed changes
protected:
	virtual  void BeginPlay() override;
	virtual  void Tick(float DeltaTime) override;

<<<<<<< Updated upstream
=======
	UPROPERTY(EditAnywhere)
	float leftBounds;

	UPROPERTY(EditAnywhere)
	float rightBounds;

	UPROPERTY(EditAnywhere)
	UPaperFlipbookComponent* flipBook;
>>>>>>> Stashed changes
	
	
	
private:
	char currentState;
	EnemyBaseState* states[2];
	void UpdatePosition();
	void ApplyDampenForces(float DeltaTime);

};

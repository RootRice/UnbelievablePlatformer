// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyUtils.h"
#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "CollisionUtils.h"
#include "PlayerAttackingState.h"
#include "PlayerFreeState.h"
#include "PlayerCrouchState.h"
#include "PlayerDamagedState.h"
#include "MainCharacter.generated.h"

UCLASS()
class SIDESCROLLER_API AMainCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ManageState(char newState);
	void SetAnimation(char animation);
	FVector GetAttackPosition();

	void TakeDamage(char damage, FVector damageSource);
	
	bool direction;
	bool grounded;
	bool crouched;
	FVector loc;
private:
	void Jump();
	void Move(float value);
	void Attack();
	void Crouch();
	void UpdatePosition(float deltaTime);
	void ApplyDampenForces(float deltaTime);
	
	
	FVector vel;

	char health;

	char currentState;
	char currentAnimation;

	PlayerBaseState* states[4];
	PlayerFreeState state;
	
	UPROPERTY(EditAnywhere)
	FVector2D originalSize;
	
	FVector2D trueSize;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* capsule;
	
	UPROPERTY(EditAnywhere)
	USpringArmComponent* springArm;

	UPROPERTY(EditAnywhere)
	UCameraComponent* camera;
	
	UPROPERTY(EditAnywhere)
	UPaperFlipbookComponent* flipBook;

	UPROPERTY(EditAnywhere)
	UPaperFlipbook* flipBooks[6];
	
	UPROPERTY(EditAnywhere)
	float jumpForce;
};

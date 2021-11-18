// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyUtils.h"
#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
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

private:
	void Jump();
	void Move(float value);
	void UpdatePosition(float deltaTime);
	void ApplyDampenForces(float deltaTime);
	UPROPERTY(VisibleAnywhere);
	FVector vel;
	float yVel;
	float xVel;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* capsule;
	
	UPROPERTY(EditAnywhere)
	USpringArmComponent* springArm;

	UPROPERTY(EditAnywhere)
	UCameraComponent* camera;
	
	UPROPERTY(EditAnywhere)
	UPaperFlipbookComponent* flipBook;
	
	UPROPERTY(EditAnywhere)
	float jumpForce;
};

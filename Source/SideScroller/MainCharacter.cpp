// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"



// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	capsule->SetupAttachment(RootComponent);
	
	flipBook = CreateDefaultSubobject<UPaperFlipbookComponent>("SpriteSheet");
	flipBook->SetupAttachment(capsule);
	
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	camera->SetupAttachment(capsule);
	
	vel = vel.ZeroVector;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdatePosition(DeltaTime);
	ApplyDampenForces(DeltaTime);
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("CustomJump", IE_Pressed, this, &AMainCharacter::Jump);
	PlayerInputComponent->BindAxis("CustomRun", this, &AMainCharacter::Move);

}

void AMainCharacter::Move(float Value)
{
	vel.X = Value * 5 * (Value != 0) + vel.X * (Value == 0);
}


void AMainCharacter::Jump()
{
	vel.Z = vel.Z * !grounded + jumpForce*grounded;
}
void AMainCharacter::UpdatePosition(float deltaTime)
{
	grounded = false;
	FVector offset = CollisionUtils::ResolveAAStaticCollisions(this->GetActorLocation(), size, &vel);
	grounded = abs(vel.Z) < 0.00001f;
	SetActorLocation(offset+this->GetActorLocation());
}
void AMainCharacter::ApplyDampenForces(float deltaTime)
{
	// yVel -= 8 * deltaTime;
	// yVel = MyUtils::Max(yVel, -64);
	//
	// xVel += (abs(xVel) > 0) * -MyUtils::Sign(xVel) * 20* deltaTime;
	// xVel = xVel * (abs(xVel) > 0.3f);
	//vel.Set(xVel, 0, yVel);
	vel.Z -= 16*deltaTime;
	vel.Z = MyUtils::Max(vel.Z, -64);

	float xVel = vel.X;
	xVel = (abs(xVel) > 0) * -MyUtils::Sign(xVel) * 20* deltaTime;
	xVel = xVel * abs(xVel) > 0.3f;
	vel.X = xVel;
}


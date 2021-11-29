// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	capsule->SetupAttachment(RootComponent);
	
	flipBook = CreateDefaultSubobject<UPaperFlipbookComponent>("SpriteSheet");
	flipBook->SetupAttachment(capsule);
	
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	camera->SetupAttachment(capsule);
	
	vel = vel.ZeroVector;
	state.StateBegin(this, &vel);
	states[0] = new PlayerFreeState();
	states[0]->StateBegin(this, &vel);
	states[1] = new PlayerCrouchState();
	states[1]->StateBegin(this, &vel);
	states[2] = new PlayerAttackingState();
	states[2]->StateBegin(this, &vel);
	crouched = false;
	currentState = 0;
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdatePosition(DeltaTime);
	ApplyDampenForces(DeltaTime);
	states[currentState]->StateTick(DeltaTime);
	flipBook->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0.0f, 0.0f, 180.0f * direction)));
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("CustomJump", IE_Pressed, this, &AMainCharacter::Jump);
	PlayerInputComponent->BindAxis("CustomRun", this, &AMainCharacter::Move);
	PlayerInputComponent->BindAction("Attack", IE_Pressed,this, &AMainCharacter::Attack);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed,this, &AMainCharacter::Crouch);

}

void AMainCharacter::ManageState(char newState)
{
	currentState = newState;
}

void AMainCharacter::SetAnimation(char animation)
{
	flipBook->SetFlipbook(flipBooks[animation]);
}

void AMainCharacter::Move(float Value)
{
	states[currentState]->StateInput(0, Value * 5 * (Value != 0) + vel.X * (Value == 0));
}

void AMainCharacter::Attack()
{
	states[currentState]->StateInput(2, 0);
}

void AMainCharacter::Crouch()
{
	states[currentState]->StateInput(3, grounded);
}


void AMainCharacter::Jump()
{
	states[currentState]->StateInput(1, !grounded + jumpForce*grounded);
}
void AMainCharacter::UpdatePosition(float deltaTime)
{
	
	const FVector actorLoc = this->GetActorLocation();

	//Check crouching//
	const int halfSize = int(originalSize.Y) >> 1;
	trueSize = FVector2D(originalSize.X, halfSize + halfSize*!crouched);
	FVector crouchAdjust(0.0f, 0.0f, (halfSize >>1)*crouched);
	loc = actorLoc-crouchAdjust;

	//Check collision//
	grounded = false;
	FVector offset = CollisionUtils::ResolveAAStaticCollisions(loc, trueSize, &vel);
	grounded = abs(vel.Z) < 0.00001f;

	//Update location//
	SetActorLocation(offset+actorLoc);
	//UE_LOG(LogTemp, Warning, TEXT("Crouched: %s"), *f.ToString());
}
void AMainCharacter::ApplyDampenForces(float deltaTime)
{
	vel.Z -= 16*deltaTime;
	vel.Z = MyUtils::Max(vel.Z, -64);

	float xVel = vel.X;
	xVel += (abs(xVel) > 0) * -MyUtils::Sign(xVel) *20* deltaTime;
	xVel = xVel * (abs(xVel) > 1.0f);
	vel.X = xVel;
}


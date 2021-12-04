// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

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
	states[3] = new PlayerDamagedState();
	states[3]->StateBegin(this, &vel);
	crouched = false;
	currentState = 0;
	health = 30;
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	CollisionUtils::SetPlayer(&loc, &trueSize, this);
}

void AMainCharacter::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	UpdatePosition(deltaTime);
	ApplyDampenForces(deltaTime);
	states[currentState]->StateTick(deltaTime);
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
	PlayerInputComponent->BindAction("Escape", IE_Pressed,this, &AMainCharacter::Quit);

}

void AMainCharacter::ManageState(char newState)
{
	currentState = newState;
}

void AMainCharacter::SetAnimation(char animation)
{
	flipBook->SetFlipbook(flipBooks[animation]);
}

FVector AMainCharacter::GetAttackPosition()
{
	FVector attackLoc = this->GetActorLocation() + (FVector(originalSize.X * 2, 0.0f, 0.0f) * (1-!direction*2));
	//DrawDebugPoint(GetWorld(), attackLoc + FVector(0, -0.1f, 0), 100,FColor(52, 220, 239), false, 2.0f);
	return attackLoc;
}

void AMainCharacter::TakeDamage(char damage, FVector damageSource)
{
	//DrawDebugPoint(GetWorld(), damageSource + FVector(0, -0.1f, 0), 150,FColor(52, 220, 239), false, 2.0f);
	const char damageToTake = states[currentState]->TakeDamage(damage);
	const char dir = MyUtils::Sign(loc.X - damageSource.X);
	const bool shouldMove = damageToTake != 0;
	UE_LOG(LogTemp, Warning, TEXT("damaged: %i"), shouldMove);
	vel = FVector(1.2f*shouldMove*dir + vel.X *!shouldMove, 0.0f, 0.8f*shouldMove + vel.Z*!shouldMove);
	health -= damageToTake;
	if(health < 1)
	{
		CollisionUtils::Reset();
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
}

void AMainCharacter::Move(float Value)
{
	states[currentState]->StateInput(0, Value * 1.7f* (Value != 0) + vel.X * (Value == 0));
}

void AMainCharacter::Attack()
{
	states[currentState]->StateInput(2, 0);
}

void AMainCharacter::Crouch()
{
	states[currentState]->StateInput(3, grounded);
}

void AMainCharacter::Quit()
{
	FGenericPlatformMisc::RequestExit(false);
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
	vel.Z -= 4*deltaTime;
	vel.Z = MyUtils::Max(vel.Z, -64);

	float xVel = vel.X;
	xVel += (abs(xVel) > 0) * -MyUtils::Sign(xVel) *4* deltaTime;
	xVel = xVel * (abs(xVel) > 1.0f);
	vel.X = xVel;
}


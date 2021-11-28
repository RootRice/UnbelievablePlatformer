// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySoldier.h"

#include "MainCharacter.h"


AEnemySoldier::AEnemySoldier()
{
	PrimaryActorTick.bCanEverTick = true;
	currentState = 0;
	states[0] = new EnemyFreeState();
}

AEnemySoldier::~AEnemySoldier()
{
}

void AEnemySoldier::BeginPlay()
{
	Super::BeginPlay();
	AMainCharacter* character;
	character = FindObject<AMainCharacter>(NULL, false);
	CollisionUtils::AddEnemy(loc, FVector(SpriteSize.X, 0.0f, SpriteSize.Y));
	states[0]->StateBegin(this, &character->loc);
}

void AEnemySoldier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	states[currentState]->StateTick(DeltaTime);
	ApplyDampenForces(DeltaTime);
	UpdatePosition();
}

void AEnemySoldier::ManageStates(char newState)
{
	
}

void AEnemySoldier::UpdatePosition()
{
	FVector offset = CollisionUtils::ResolveAAStaticCollisions(this->GetActorLocation(), SpriteSize, &vel);
	this->SetActorLocation(offset+this->GetActorLocation());
}

void AEnemySoldier::ApplyDampenForces(float DeltaTime)
{
	vel.Z -= 8 * DeltaTime;
	vel.Z = MyUtils::Min(vel.Z, -64);

	float xVel = vel.X;
	xVel += (abs(xVel) > 0) * -MyUtils::Sign(xVel) *20* DeltaTime;
	xVel = xVel * (abs(xVel) > 0.3f);
	vel.X = xVel;
}

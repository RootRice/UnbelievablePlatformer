// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySoldier.h"

#include "MainCharacter.h"
<<<<<<< Updated upstream
=======
#include "Kismet/GameplayStatics.h"
>>>>>>> Stashed changes


AEnemySoldier::AEnemySoldier()
{
<<<<<<< Updated upstream
=======
	flipBook = CreateDefaultSubobject<UPaperFlipbookComponent>("SpriteSheet");
	flipBook->SetupAttachment(RootComponent);

	
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
	AMainCharacter* character;
	character = FindObject<AMainCharacter>(NULL, false);
	CollisionUtils::AddEnemy(loc, FVector(SpriteSize.X, 0.0f, SpriteSize.Y));
	states[0]->StateBegin(this, &character->loc);
=======
	CollisionUtils::AddEnemy(loc, FVector(SpriteSize.X, 0.0f, SpriteSize.Y));
	APawn* pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	AMainCharacter* MainCharacter = Cast<AMainCharacter>(pawn);
	states[0]->StateBegin(this, &MainCharacter->loc, leftBounds, rightBounds);
>>>>>>> Stashed changes
}

void AEnemySoldier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	states[currentState]->StateTick(DeltaTime);
	ApplyDampenForces(DeltaTime);
	UpdatePosition();
<<<<<<< Updated upstream
=======

	this->SetActorRotation(FQuat::MakeFromEuler(FVector(0.0f, 0.0f, 180.0f * direction)));
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
	vel.Z = MyUtils::Min(vel.Z, -64);
=======
	vel.Z = MyUtils::Max(vel.Z, -64);
>>>>>>> Stashed changes

	float xVel = vel.X;
	xVel += (abs(xVel) > 0) * -MyUtils::Sign(xVel) *20* DeltaTime;
	xVel = xVel * (abs(xVel) > 0.3f);
	vel.X = xVel;
}

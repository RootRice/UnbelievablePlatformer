// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySoldier.h"

#include "MainCharacter.h"
#include "EnemyStates/EnemyPrepAttackState.h"
#include "Kismet/GameplayStatics.h"


AEnemySoldier::AEnemySoldier()
{
	flipBook = CreateDefaultSubobject<UPaperFlipbookComponent>("SpriteSheet");
	flipBook->SetupAttachment(RootComponent);
	
	PrimaryActorTick.bCanEverTick = true;
	currentState = 0;
	loc = new FVector();
	states[0] = new EnemyFreeState();
	states[1] = new EnemyPrepAttackState();
}

AEnemySoldier::~AEnemySoldier()
{
}

void AEnemySoldier::BeginPlay()
{
	Super::BeginPlay();
	CollisionUtils::AddAAEnemy(loc, FVector(SpriteSize.X, 0.0f, SpriteSize.Y), this);
	APawn* pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	AMainCharacter* MainCharacter = Cast<AMainCharacter>(pawn);
	states[0]->StateBegin(this, &MainCharacter->loc, leftBounds, rightBounds);
	states[1]->StateBegin(this, &MainCharacter->loc, attackPrepDuration);
}

void AEnemySoldier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	states[currentState]->StateTick(DeltaTime);
	ApplyDampenForces(DeltaTime);
	UpdatePosition();

	this->SetActorRotation(FQuat::MakeFromEuler(FVector(0.0f, 0.0f, 180.0f * direction)));
}

void AEnemySoldier::ManageStates(char newState)
{
	currentState = newState;
}

void AEnemySoldier::TakeDamage(char damage)
{
	health -= damage;
	UE_LOG(LogTemp, Warning, TEXT("HIT: %i"), damage);
	states[currentState]->TakeDamage();
}

void AEnemySoldier::UpdatePosition()
{
	FVector offset = CollisionUtils::ResolveAAStaticCollisions(this->GetActorLocation(), SpriteSize, &vel);
	*loc = offset+this->GetActorLocation();
	this->SetActorLocation(*loc);
}

void AEnemySoldier::ApplyDampenForces(float DeltaTime)
{
	vel.Z -= 8 * DeltaTime;
	vel.Z = MyUtils::Max(vel.Z, -64);
	float xVel = vel.X;
	xVel += (abs(xVel) > 0) * -MyUtils::Sign(xVel) *20* DeltaTime;
	xVel = xVel * (abs(xVel) > 0.3f);
	vel.X = xVel;
}

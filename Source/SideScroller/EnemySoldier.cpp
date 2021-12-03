// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySoldier.h"

#include "EnemyAttackState.h"
#include "MainCharacter.h"
#include "EnemyStates/EnemyPrepAttackState.h"
#include "EnemyStates/EnemyRecoilState.h"
#include "Kismet/GameplayStatics.h"


AEnemySoldier::AEnemySoldier()
{
	flipBook = CreateDefaultSubobject<UPaperFlipbookComponent>("SpriteSheet");
	flipBook->SetupAttachment(RootComponent);
	
	PrimaryActorTick.bCanEverTick = true;
	currentState = 0;
	loc = new FVector();
	states[0] = new EnemyFreeState();
	states[1] = new EnemyRecoilState();
	states[2] = new EnemyPrepAttackState();
	states[3] = new EnemyAttackState();
	invulnTimer = 0;
	damageable = true;
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
	states[1]->StateBegin(this, &MainCharacter->loc);
	states[2]->StateBegin(this, &MainCharacter->loc, attackPrepDuration);
	states[3]->StateBegin(this, &MainCharacter->loc);
}

void AEnemySoldier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//State management//
	states[currentState]->StateTick(DeltaTime);

	//Transform management//
	ApplyDampenForces(DeltaTime);
	UpdatePosition();
	this->SetActorRotation(FQuat::MakeFromEuler(FVector(0.0f, 0.0f, 180.0f * direction)));

	//Damage management//
	invulnTimer += DeltaTime;
	damageable |= invulnTimer > 1.5f;
	invulnTimer *= !damageable;
}

void AEnemySoldier::ManageStates(char newState)
{
	currentState = newState;
}

void AEnemySoldier::Animate(char animation)
{
	flipBook->SetFlipbook(animations[animation]);
}

void AEnemySoldier::LaunchAttack(bool attackHeight)
{
	FVector2D a(150, 30);
	FVector offset(75*(1-!(direction)*2), 0.0f, 150*(1-attackHeight*2));
	CollisionUtils::ResolvePlayerHit(*loc-offset, a, 3);
	currentState = 3;
	Animate(4+attackHeight);
}

void AEnemySoldier::TakeDamage(char damage)
{
	const char damageToTake = states[currentState]->TakeDamage(damage*damageable);
	health -= damageToTake;
	damageable &= (damageToTake == 0);
	invulnTimer *= !damageable;
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

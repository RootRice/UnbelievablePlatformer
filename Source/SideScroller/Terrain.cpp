// Fill out your copyright notice in the Description page of Project Settings.


#include "Terrain.h"

ATerrain::ATerrain()
{
	PrimaryActorTick.bCanEverTick = false;
	spriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite");
	spriteComponent->SetupAttachment(RootComponent);
}

ATerrain::~ATerrain()
{
}

void ATerrain::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionUtils::AddStaticAxisAligned(this->GetActorLocation(), SpriteSize);
	
}
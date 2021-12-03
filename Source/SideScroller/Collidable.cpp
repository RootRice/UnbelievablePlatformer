// Fill out your copyright notice in the Description page of Project Settings.


#include "Collidable.h"

// Sets default values
ACollidable::ACollidable()
{
	PrimaryActorTick.bCanEverTick = false;
}
void ACollidable::BeginPlay()
{
	Super::BeginPlay();
	if(isStatic)
	{
		if(isAligned)
		{
			CollisionUtils::AddStaticAxisAligned(this->GetActorLocation(), SpriteSize);
		}
		else
		{
			
		}
	}
	else
	{
		if(isAligned)
		{
			loc = new FVector(this->GetActorLocation());
		}
		else
		{
			
		}
	}
}


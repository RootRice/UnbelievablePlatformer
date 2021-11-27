// Fill out your copyright notice in the Description page of Project Settings.


#include "Collidable.h"

// Sets default values
ACollidable::ACollidable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	sprite = CreateDefaultSubobject<UPaperSprite>("Sprite");
	

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
			CollisionUtils::AddDynamicAxisAligned(loc, size);
		}
		else
		{
			
		}
	}
}


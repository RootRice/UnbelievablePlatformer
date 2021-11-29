// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollisionUtils.h"
#include "Paper2D/Classes/PaperSpriteActor.h"
#include "Paper2D/Classes/PaperSpriteComponent.h"
#include "Collidable.generated.h"

UCLASS()
class SIDESCROLLER_API ACollidable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollidable();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	FVector2D SpriteSize;
	
	FVector* loc;
	FVector* size;
	
private:
	UPROPERTY(EditAnywhere)
	bool isStatic;
	UPROPERTY(EditAnywhere)
	bool isAligned;
	
	
	
	
};

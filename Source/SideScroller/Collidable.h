// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollisionUtils.h"
#include "MainCharacter.h"
#include "Paper2D/Classes/PaperSpriteActor.h"
#include "Paper2D/Classes/PaperSprite.h"
#include "Collidable.generated.h"

UCLASS()
class SIDESCROLLER_API ACollidable : public APaperSpriteActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollidable();

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere)
	bool isStatic;
	UPROPERTY(EditAnywhere)
	bool isAligned;
	
	FVector* loc;
	FVector* size;
	
	UPROPERTY(EditAnywhere)
	UPaperSprite* sprite;
};

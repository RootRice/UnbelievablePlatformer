// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collidable.h"
#include "Terrain.generated.h"
/**
 * 
 */
UCLASS()
class SIDESCROLLER_API ATerrain : public ACollidable
{
	GENERATED_BODY()
public:
	ATerrain();
	~ATerrain();

protected:
	virtual void BeginPlay() override;
	
private:

	UPROPERTY(EditAnywhere)
	UPaperSpriteComponent* spriteComponent;
	
};

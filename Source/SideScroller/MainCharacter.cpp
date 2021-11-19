// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"



// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	capsule->SetupAttachment(RootComponent);
	
	flipBook = CreateDefaultSubobject<UPaperFlipbookComponent>("SpriteSheet");
	flipBook->SetupAttachment(capsule);
	
	springArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	springArm->SetupAttachment(capsule);
	
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	camera->SetupAttachment(springArm);
	
	xVel = 0;
	yVel = 0;
	vel = vel.ZeroVector;

	size = FVector2D(flipBook->Bounds.BoxExtent.X, flipBook->Bounds.BoxExtent.Z);
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdatePosition(DeltaTime);
	ApplyDampenForces(DeltaTime);
	CollisionUtils::CheckStaticCollisions(this->GetActorLocation(), size);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);
	PlayerInputComponent->BindAxis("CustomRun", this, &AMainCharacter::Move);

}

void AMainCharacter::Move(float Value)
{
	xVel = 5 * Value;
}

void AMainCharacter::Jump()
{
	yVel = 64;
}
void AMainCharacter::UpdatePosition(float deltaTime)
{
	SetActorLocation(GetActorLocation() + vel);
}
void AMainCharacter::ApplyDampenForces(float deltaTime)
{
	yVel -= 8 * deltaTime;
	yVel = MyUtils::Max(yVel, -64);
	
	xVel -= (abs(xVel) > 0) * -MyUtils::Sign(xVel) * 2.0f* deltaTime;
	xVel = xVel * (xVel > 0.3f);
	vel.Set(xVel, 0, yVel);
}


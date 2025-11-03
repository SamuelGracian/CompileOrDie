// Fill out your copyright notice in the Description page of Project Settings.


#include "Whip.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"


// Sets default values
AWhip::AWhip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
}

// Called when the game starts or when spawned
void AWhip::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentRotation = GetActorRotation();
	TargetRotation = CurrentRotation;
}

// Called every frame
void AWhip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TargetRotation.Yaw += Input * RotationSpeed * DeltaTime;

	float DeltaYaw = FMath::FindDeltaAngleDegrees(CurrentRotation.Yaw, TargetRotation.Yaw);

	float Overshoot = FMath::Clamp(DeltaYaw, -OverShootAmount, OverShootAmount);

	CurrentRotation.Yaw = FMath::Sin(GetWorld()->GetTimeSeconds() * WhipStrength) * Overshoot + Input;

	SetActorRotation(CurrentRotation);
}

// Called to bind functionality to input
void AWhip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AWhip::MoveYaw(float value)
{
	Input = value;
}
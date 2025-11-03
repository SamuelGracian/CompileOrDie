// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Whip.generated.h"

UCLASS()
class COMPILEORDIE_API AWhip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AWhip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Whip movement")
	float RotationSpeed = 90.0f;

	UPROPERTY(EditAnywhere, Category = "Whip movement")
	float WhipStrength = 6.0f;

	UPROPERTY(EditAnywhere, Category = "Whip movement")
	float OverShootAmount = 10.0f;

	FRotator CurrentRotation;
	FRotator TargetRotation;

	float Input = 0.0f;

public: 
	
	void MoveYaw(float value);

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpaceShipChar.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class USplineComponent;

//DECLARE_LOG_CATEGORY_EXTERN(LogStarfox, Log, All);

UCLASS()
class COMPILEORDIE_API ASpaceShipChar : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveForwardAction;
	

public:
	// Sets default values for this character's properties
	ASpaceShipChar();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void TurnRight(const FInputActionValue& Value);
	void MoveUp (const FInputActionValue& Value);
	void TurnLeft(const FInputActionValue& Value);
	void Pitch(const FInputActionValue& Value);
	void Roll(const FInputActionValue& Value);

	float GetCurrentDistanceOnSpline() const;

protected:

	virtual void NotifyControllerChanged() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	///<summary>
	/// Flight path
	///</summary>
	UPROPERTY(EditAnywhere, Category = "Flight Path")
	class USplineComponent* FlightPath;

	UPROPERTY(EditAnywhere, Category = "Flight Path")
	float SplineProgress = 0.0f; // from 0.0 a 1.0

	UPROPERTY(EditAnywhere, Category = "Flight Path")
	float PathSpeed = 300.0f; // Speed along the spline

	UPROPERTY(EditAnywhere, Category = "Flight Bounds")
	float HorizontalLimit = 300.0f;

	UPROPERTY(EditAnywhere, Category = "Flight Bounds")
	float VerticalLimit = 200.0f;

	FVector2D ScreenOffset; // Movement inside the bounds}

	UPROPERTY(EditAnywhere, Category = "Flight Path")
	float CurrentDistaneOnSpline = 300.0f;

	/// <summary>
	/// Movement and Rotation Speeds
	/// </summary>
	UPROPERTY(EditAnywhere, Category = "Flight")
	float MoveSpeed = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Flight")
	float TurnSpeed = 50.0f;

	UPROPERTY(EditAnywhere, Category = "Flight")
	float PitchSpeed = 50.0f;

	UPROPERTY(EditAnywhere, Category = "Flight")
	float RollSpeed = 50.0f;

	UPROPERTY(EditAnywhere, Category = "Flight")
	float RotationInterpSpeed = 5.0f; //Visualize the spinning

	//UPROPERTY(EditDefaultsOnly, Category = "Components") class UStaticMeshComponent* SpaceShipMesh;

	FVector MovementInput;

	float YawInput;
	float PitchInput;
	float RollInput;
};

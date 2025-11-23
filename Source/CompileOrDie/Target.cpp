// Fill out your copyright notice in the Description page of Project Settings.

#include "Target.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
ATarget::ATarget()
{
	PrimaryActorTick.bCanEverTick = true;

	// Crear spring arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;

	// Crear cámara
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Rotación de cámara según input del jugador
	AddControllerYawInput(CameraInput.X * LookSpeed * DeltaTime);
	AddControllerPitchInput(CameraInput.Y * LookSpeed * DeltaTime);
}

// Called to bind functionality to input
void ATarget::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Enhanced Input binding
	if (UEnhancedInputComponent* EI = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Make sure MoveAction is valid before binding
		if (MoveAction)
		{
			EI->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATarget::Move);
		}
	}
}

void ATarget::Move(const FInputActionValue& value)
{
	FVector2D MovementVector = value.Get<FVector2D>();

	//FVector ShipLocalOffset;

	if (!Controller) return;
	
	///Horizontal rotation
	FRotator CamRotation = Controller->GetControlRotation();
	CamRotation.Pitch = 0.0f;
	CamRotation.Roll = 0.0f;

	///Direction based on camera
	FVector UpVector = FRotationMatrix(CamRotation).GetUnitAxis(EAxis::X);
	FVector RightVector = FRotationMatrix(CamRotation).GetUnitAxis(EAxis::Y);

	FVector LocalOffset =
		UpVector * MovementVector.Y +
		RightVector * MovementVector.X;

	///Offset respect to spline
	//ShipLocalOffset += LocalOffset * MoveSpeed;


}

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

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController) return;

	// Obtener el Enhanced Input Local Player Subsystem
	if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
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

	if (UEnhancedInputComponent* EI = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EI->BindAction(AimAction, ETriggerEvent::Triggered, this, &ATarget::Aim);
		EI->BindAction(AimAction, ETriggerEvent::Completed, this, &ATarget::StopAiming);
	}
}


void ATarget::Aim(const FInputActionValue& value)
{
	// Read aim as a 2D axis and feed it into Character movement.
	FVector2D MovementVector = value.Get<FVector2D>();

	if (!Controller) return;

	FRotator CamRotation = Controller->GetControlRotation();
	CamRotation.Pitch = 0.0f;
	CamRotation.Roll = 0.0f;

	FVector Forward = FRotationMatrix(CamRotation).GetUnitAxis(EAxis::X);
	FVector Right = FRotationMatrix(CamRotation).GetUnitAxis(EAxis::Y);

	if (FMath::Abs(MovementVector.Y) > KINDA_SMALL_NUMBER)
	{
		AddMovementInput(Forward, MovementVector.Y);
	}
	if (FMath::Abs(MovementVector.X) > KINDA_SMALL_NUMBER)
	{
		AddMovementInput(Right, MovementVector.X);
	}
}

void ATarget::StopAiming(const FInputActionValue& Value)
{
	AimVector = FVector2D::ZeroVector;
}
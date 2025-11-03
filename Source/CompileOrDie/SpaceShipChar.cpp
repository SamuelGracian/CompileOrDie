// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShipChar.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/SplineComponent.h"

//DEFINE_LOG_CATEGORY(LogStarfox);

// Sets default values
ASpaceShipChar::ASpaceShipChar()
{
	PrimaryActorTick.bCanEverTick = true;

	//SpaceShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpaceShipMesh"));
	//SpaceShipMesh->SetupAttachment(RootComponent);

	FlightPath = CreateDefaultSubobject<USplineComponent>(TEXT("FlightPath"));
	FlightPath->SetupAttachment(RootComponent);

	GetCharacterMovement()->GravityScale = 0.0f;
	GetCharacterMovement()->SetMovementMode(MOVE_Flying);

}

void ASpaceShipChar::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
		else if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(MappingContext, 0);
		}
	}
}

// Called when the game starts or when spawned
void ASpaceShipChar::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpaceShipChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SplineProgress += (PathSpeed * DeltaTime) / FlightPath->GetSplineLength();
	SplineProgress = FMath::Fmod(SplineProgress, 1.0f);

	FVector BaseLocation = FlightPath->GetLocationAtTime(SplineProgress, ESplineCoordinateSpace::World, true);
	FRotator BaseRotation = FlightPath->GetRotationAtTime(SplineProgress, ESplineCoordinateSpace::World, true);

	FVector LocalOffset = FVector(ScreenOffset.X, 0.0f, ScreenOffset.Y);
	FVector OffsetWorld = BaseRotation.RotateVector(LocalOffset);

	SetActorLocation(BaseLocation + OffsetWorld);

	SetActorRotation(BaseRotation);

	float TargetRoll = -ScreenOffset.X * 0.1f;
	FRotator VisualRot = GetActorRotation();
	VisualRot.Roll = FMath::FInterpTo(VisualRot.Roll, TargetRoll, DeltaTime, 3.0f);
	SetActorRotation(VisualRot);
}

///---------------------------------------------------------
///Binding Input
///---------------------------------------------------------
// Called to bind functionality to input
void ASpaceShipChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
	
}

void ASpaceShipChar::TurnRight(const FInputActionValue& Value)
{
	FVector2D AxisValue = Value.Get<FVector2D>() ;
	//UE_LOG(LogStarfox, Display, TEXT("Right input actioned."));
	ScreenOffset.X = FMath::Clamp(ScreenOffset.X + AxisValue.X * 5.0f, -HorizontalLimit, HorizontalLimit);
}

void ASpaceShipChar::MoveUp(const FInputActionValue& Value)
{
	FVector2D AxisValue = Value.Get<FVector2D>();
	//UE_LOG(LogStarfox, Display, TEXT("Up input actioned."));
	ScreenOffset.Y = FMath::Clamp(ScreenOffset.Y+ AxisValue.Y * 5.0f, -VerticalLimit , VerticalLimit);
}

void ASpaceShipChar::TurnLeft(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	//UE_LOG(LogStarfox, Display, TEXT("Turn input actioned."));
}

void ASpaceShipChar::Pitch(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	//UE_LOG(LogStarfox, Display, TEXT("Pitch input actioned."));
}

void ASpaceShipChar::Roll(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	//UE_LOG(LogStarfox, Display, TEXT("Roll input actioned."));
}
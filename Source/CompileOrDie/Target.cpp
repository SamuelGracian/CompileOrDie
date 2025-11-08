// Fill out your copyright notice in the Description page of Project Settings.

#include "Target.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ATarget::ATarget()
{
	// Enable ticking
	PrimaryActorTick.bCanEverTick = true;

	// Create and attach a spring arm to the character's root (capsule)
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	if (SpringArm)
	{
		SpringArm->SetupAttachment(GetRootComponent());
		SpringArm->TargetArmLength = 300.0f; // default distance

		// Let the arm inherit controller rotation so the camera orbits the character, but use rotation lag to create the "whip" feel
		SpringArm->bUsePawnControlRotation = true;

		// Enable location lag and tune defaults for a whip-like feel
		SpringArm->bEnableCameraLag = true;
		SpringArm->CameraLagSpeed = 6.0f;            // lower = more lag (follow more slowly)
		SpringArm->CameraLagMaxDistance = 200.0f;    // max distance the camera target may lag

		// Enable rotation lag so the camera rotation trails slightly
		SpringArm->bEnableCameraRotationLag = true;
		SpringArm->CameraRotationLagSpeed = 10.0f;   // higher = snaps faster for rotation

		// Use substepping to keep lag stable across variable framerates
		SpringArm->bUseCameraLagSubstepping = true;
		SpringArm->CameraLagMaxTimeStep = 0.016f;    // 60 Hz cap for substepping
	}

	// Create and attach camera to the spring arm
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	if (CameraComponent)
	{
		CameraComponent->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
		CameraComponent->bUsePawnControlRotation = false; 
	}

}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();

	//if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	//{
	//	PlayerController->SetShowMouseCursor(true);
	//	PlayerController->SetInputMode(FInputModeGameAndUI());
	//	PlayerController->Possess(this);
	//}
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (!SpringArm)
	//{
	//	return;
	//}

	//Speed = GetVelocity().Size();

	//TargetCameraLagSpeed = FMath::GetMappedRangeValueClamped(FVector2D(0.0f, 800.0f), FVector2D(18.0f, 3.0f), Speed);


	//TargetCameraRotationLagSpeed = FMath::GetMappedRangeValueClamped(FVector2D(0.0f, 800.0f), FVector2D(20.0f, 6.0f), Speed);

	//InterpSpeed = 6.0f; // higher = faster interpolation
	//SpringArm->CameraLagSpeed = FMath::FInterpTo(SpringArm->CameraLagSpeed, TargetCameraLagSpeed, DeltaTime, InterpSpeed);
	//SpringArm->CameraRotationLagSpeed = FMath::FInterpTo(SpringArm->CameraRotationLagSpeed, TargetCameraRotationLagSpeed, DeltaTime, InterpSpeed);

}

// Called to bind functionality to input
void ATarget::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


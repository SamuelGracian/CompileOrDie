#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SplineComponent.h"
#include "Target.generated.h"
#include "InputAction.h"

struct FInputActionValue;

UCLASS()
class COMPILEORDIE_API ATarget : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& value);

	// --- Camera ---
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* Camera;

	// Relative Movement (player input)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	FVector2D CameraInput = FVector2D::ZeroVector;

	// Sens to move the camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float LookSpeed = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "SplineCamera.generated.h"

class USplineComponent;

UCLASS()
class COMPILEORDIE_API ASplineCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplineCamera();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Default spline component
	UPROPERTY(EditAnywhere, Category = "Spline")
	USplineComponent* SplineComponent;

	// Units along the spline
	UPROPERTY(EditAnywhere, Category = "Spline")
	float PathSpeed = 100.0f;

	// Bounding limits for offset relative to spline position.
	UPROPERTY(EditAnywhere, Category = "Bounds")
	float HorizontalLimit = 300.0f;

	UPROPERTY(EditAnywhere, Category = "Bounds")
	float VerticalLimit = 200.0f;

	UPROPERTY(EditAnywhere, Category = "Bounds")
	bool bUseViewportLimits = true;

	UPROPERTY(EditAnywhere, Category = "Interp")
	float PositionInterpSpeed = 6.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Update HorizontalLimit/VerticalLimit from the active viewport and camera.
	void UpdateLimitsFromViewport(const FVector& PlanePoint);

	float m_currentDistance = 0.0f;

};

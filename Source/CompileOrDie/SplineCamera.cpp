// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineCamera.h"

// Sets default values
ASplineCamera::ASplineCamera()
{
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASplineCamera::BeginPlay()
{
	Super::BeginPlay();

	m_currentDistance = 0.0f;
	
}

// Called every frame
void ASplineCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!SplineComponent) return;

    const float SplineLength = SplineComponent->GetSplineLength();
    if (SplineLength <= KINDA_SMALL_NUMBER) return;

    // Advance along spline (wrap around)
    m_currentDistance += PathSpeed * DeltaTime;
    if (m_currentDistance > SplineLength) m_currentDistance = FMath::Fmod(m_currentDistance, SplineLength);

    // Base transform on spline
    const FVector SplineLocation = SplineComponent->GetLocationAtDistanceAlongSpline(m_currentDistance, ESplineCoordinateSpace::World);
    const FRotator SplineRotation = SplineComponent->GetRotationAtDistanceAlongSpline(m_currentDistance, ESplineCoordinateSpace::World);

    FVector DesiredLocation = SplineLocation;

    // Smooth position & rotation
    const FVector NewLocation = FMath::VInterpTo(GetActorLocation(), DesiredLocation, DeltaTime, PositionInterpSpeed);
    const FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), SplineRotation, DeltaTime, PositionInterpSpeed);

    SetActorLocationAndRotation(NewLocation, NewRotation);

}


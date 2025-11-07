// Fill out your copyright notice in the Description page of Project Settings.

#include "SplineCamera.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"

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

    m_currentDistance += PathSpeed * DeltaTime;
    if (m_currentDistance > SplineLength) m_currentDistance = FMath::Fmod(m_currentDistance, SplineLength);

    const FVector SplineLocation = SplineComponent->GetLocationAtDistanceAlongSpline(m_currentDistance, ESplineCoordinateSpace::World);
    const FRotator SplineRotation = SplineComponent->GetRotationAtDistanceAlongSpline(m_currentDistance, ESplineCoordinateSpace::World);

    if (bUseViewportLimits)
    {
        UpdateLimitsFromViewport(SplineLocation);
    }

    FVector DesiredLocation = SplineLocation;

    // Smooth position & rotation
    const FVector NewLocation = FMath::VInterpTo(GetActorLocation(), DesiredLocation, DeltaTime, PositionInterpSpeed);
    const FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), SplineRotation, DeltaTime, PositionInterpSpeed);

    SetActorLocationAndRotation(NewLocation, NewRotation);

}

void ASplineCamera::UpdateLimitsFromViewport(const FVector& PlanePoint)
{
    // Get player controller / camera
    APlayerController* PlayerControllers = UGameplayStatics::GetPlayerController(this, 0);
    if (!PlayerControllers || !PlayerControllers->PlayerCameraManager) return;

    int32 ViewPortX = 0, ViewPortY = 0;
    PlayerControllers->GetViewportSize(ViewPortX, ViewPortY);
    if (ViewPortX <= 0 || ViewPortY <= 0) return;

    const FVector2D CenterScreen((float)ViewPortX * 0.5f, (float)ViewPortY * 0.5f);
    const FVector2D RightScreen((float)ViewPortX - 1.0f, (float)ViewPortY * 0.5f); // right middle
    const FVector2D TopScreen((float)ViewPortX * 0.5f, 0.0f);               // top middle


    FVector CenterOrigin, CenterDir;
    FVector RightOrigin, RightDir;
    FVector TopOrigin, TopDir;

    const bool bCenter = PlayerControllers->DeprojectScreenPositionToWorld(CenterScreen.X, CenterScreen.Y, CenterOrigin, CenterDir);
    const bool bRight  = PlayerControllers->DeprojectScreenPositionToWorld(RightScreen.X, RightScreen.Y, RightOrigin, RightDir);
    const bool bTop    = PlayerControllers->DeprojectScreenPositionToWorld(TopScreen.X, TopScreen.Y, TopOrigin, TopDir);

    if (!bCenter || !bRight || !bTop) return;


    const FVector CamForward = PlayerControllers->PlayerCameraManager->GetCameraRotation().Vector();
    const FVector PlaneNormal = CamForward.GetSafeNormal();

    auto IntersectRayPlane = [&](const FVector& RayOrigin, const FVector& RayDir) -> FVector
    {
        const float Denom = FVector::DotProduct(RayDir, PlaneNormal);
        if (FMath::Abs(Denom) < KINDA_SMALL_NUMBER)
        {

            const float ApproxDist = FVector::Dist(RayOrigin, PlanePoint);
            return RayOrigin + RayDir * ApproxDist;
        }
        const float T = FVector::DotProduct(PlanePoint - RayOrigin, PlaneNormal) / Denom;
        return RayOrigin + RayDir * T;
    };

    const FVector CenterWorld = IntersectRayPlane(CenterOrigin, CenterDir);
    const FVector RightWorld  = IntersectRayPlane(RightOrigin, RightDir);
    const FVector TopWorld    = IntersectRayPlane(TopOrigin, TopDir);

    const float NewHorizontalLimit = FVector::Dist(CenterWorld, RightWorld);
    const float NewVerticalLimit = FVector::Dist(CenterWorld, TopWorld);

    HorizontalLimit = FMath::Max(10.0f, NewHorizontalLimit);
    VerticalLimit = FMath::Max(10.0f, NewVerticalLimit);
}


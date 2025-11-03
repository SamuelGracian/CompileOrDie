// Fill out your copyright notice in the Description page of Project Settings.


#include "Prize.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APrize::APrize()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject <UBoxComponent>(TEXT("BoxCollider"));
	RootComponent = BoxCollider;

	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	EnemyMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APrize::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APrize::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


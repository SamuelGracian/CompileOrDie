// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Actor.h"

ADefaultGameMode::ADefaultGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/bluepriont/MyCharacter"));
	DefaultPawnClass =  PlayerPawnClassFinder.Class;
}
void ADefaultGameMode::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("DefaultGameMode has started!"));
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Prize.generated.h"

UCLASS()
class COMPILEORDIE_API APrize : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APrize();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int GetPrizeValue() const { return PrizeValue; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Components") 
	class UBoxComponent* BoxCollider;

	UPROPERTY(EditDefaultsOnly, Category = "Components") 
	class UStaticMeshComponent* EnemyMesh;
	
	UPROPERTY(BlueprintReadWrite, Category = "Prize")
	int PrizeValue;

};

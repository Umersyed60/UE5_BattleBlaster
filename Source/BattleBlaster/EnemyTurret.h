// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicPawn.h"

#include "Tank.h"

#include "EnemyTurret.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API AEnemyTurret : public ABasicPawn
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	AEnemyTurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float FireRange = 300.0f;

	UPROPERTY(EditAnywhere)
	float FireRate = 2.0f;

	UPROPERTY(VisibleAnywhere)
	ATank* Tank;

	void CheckFireCondition();

	bool IsInFireRange();

	void HandleDestruction();
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTurret.h"

AEnemyTurret::AEnemyTurret()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyTurret::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Tank) {
		float DistanceToTank = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		if (DistanceToTank < FireRange) {
			RotateTurrent(Tank->GetActorLocation());
		}
	}
}

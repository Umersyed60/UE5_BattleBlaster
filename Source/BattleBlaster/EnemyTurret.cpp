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

	FTimerHandle FireTimerHandle;
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &AEnemyTurret::CheckFireCondition, FireRate, true);
}

void AEnemyTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsInFireRange()) {
		RotateTurrent(Tank->GetActorLocation());
	}
}

void AEnemyTurret::CheckFireCondition() {
	if (Tank && Tank->IsAlive) {
		if (IsInFireRange()) {
			Fire();
		}
	}
}

bool AEnemyTurret::IsInFireRange()
{
	bool Result = false;

	if (Tank) {
		float DistanceToTank = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		Result = DistanceToTank <= FireRange;
	}
	return Result;
}

void AEnemyTurret::HandleDestruction() {
	Super::HandleDestruction();

	Destroy();
}

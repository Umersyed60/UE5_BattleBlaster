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

	//Function Called In Loop To Shoot Towards Tank After Specific Interval
	FTimerHandle FireTimerHandle;
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &AEnemyTurret::CheckFireCondition, FireRate, true);
}

void AEnemyTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Check If Player Is In Range Than Rotate Turret Towards Player
	if (IsInFireRange()) {
		RotateTurrent(Tank->GetActorLocation());
	}
}

//Looped Function To Fire Projectile Towards Player
void AEnemyTurret::CheckFireCondition() {
	if (Tank && Tank->IsAlive) {
		if (IsInFireRange()) {
			Fire();
		}
	}
}

//Function To Check If Player Is In Range
bool AEnemyTurret::IsInFireRange()
{
	bool Result = false;

	if (Tank) {
		float DistanceToTank = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		Result = DistanceToTank <= FireRange;
	}
	return Result;
}

//Function To Handle Enemy Turret Destruction
void AEnemyTurret::HandleDestruction() {
	Super::HandleDestruction();

	Destroy();
}

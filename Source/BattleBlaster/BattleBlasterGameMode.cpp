// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyTurret.h"

void ABattleBlasterGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> EnmyTurret;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyTurret::StaticClass(), EnmyTurret);
	EnemyTurretCount = EnmyTurret.Num();
	UE_LOG(LogTemp, Display, TEXT("Enemy Turret Count is: %d"), EnemyTurretCount);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn) {
		Tank = Cast<ATank>(PlayerPawn);
		if (!Tank) {
			UE_LOG(LogTemp, Display, TEXT("GameMode: Failed to find the tank actor!"));
		}
	}

	int32 LoopIndex = 0;
		while (LoopIndex < EnemyTurretCount) {
			AActor* EnemyTurretActor = EnmyTurret[LoopIndex];

			AEnemyTurret* EnmyTurtRef = Cast<AEnemyTurret>(EnemyTurretActor);
			if (EnmyTurtRef && Tank) {
				EnmyTurtRef->Tank = Tank;
			}
			LoopIndex++;
		}
}

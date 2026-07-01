// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyTurret.h"
#include "BattleBlasterGameInstance.h"

void ABattleBlasterGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> EnmyTurret;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyTurret::StaticClass(), EnmyTurret);
	EnemyTurretCount = EnmyTurret.Num();
	//UE_LOG(LogTemp, Display, TEXT("Enemy Turret Count is: %d"), EnemyTurretCount);

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

void ABattleBlasterGameMode::ActorDied(AActor* DeadActor)
{

	bool IsGameOver = false;

	if (DeadActor == Tank) {
		Tank->HandleDestruction();
		IsGameOver = true;
	}
	else
	{
		AEnemyTurret* DeadEnemyTurret = Cast<AEnemyTurret>(DeadActor);
		if (DeadEnemyTurret) {
			DeadEnemyTurret->HandleDestruction();

			EnemyTurretCount -= 1;
			if (EnemyTurretCount <= 0) {
				IsGameOver = true;
				IsVictory = true;
			}
		}
	}

	if (IsGameOver) {
		FString GameOverString = IsVictory ? "Victory" : "Defeat!";
		UE_LOG(LogTemp, Display, TEXT("Game State: %s"), *GameOverString);

		FTimerHandle GameOverTimerHandle;
		GetWorldTimerManager().SetTimer(GameOverTimerHandle, this, &ABattleBlasterGameMode::OnGameOverTimerTimeout, GameOverDelay, false);
	}
}

void ABattleBlasterGameMode::OnGameOverTimerTimeout()
{
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance) {
		UBattleBlasterGameInstance* BattleBlasterGameInstance = Cast<UBattleBlasterGameInstance>(GameInstance);
		if (BattleBlasterGameInstance) {
			if (IsVictory) {
				BattleBlasterGameInstance->LoadNextLevel();
			}
			else
			{
				BattleBlasterGameInstance->RestartCurrentLevel();
			}
		}
	}
}

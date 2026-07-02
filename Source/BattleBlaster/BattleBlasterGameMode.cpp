// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyTurret.h"
#include "BattleBlasterGameInstance.h"

void ABattleBlasterGameMode::BeginPlay()
{
	Super::BeginPlay();

	//Setting Enemy Turret Count in Level
	TArray<AActor*> EnmyTurret;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyTurret::StaticClass(), EnmyTurret);
	EnemyTurretCount = EnmyTurret.Num();

	//Setting Player Reference
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn) {
		Tank = Cast<ATank>(PlayerPawn);
		if (!Tank) {
			UE_LOG(LogTemp, Display, TEXT("GameMode: Failed to find the tank actor!"));
		}
	}

	//Setting Player Tank Reference in Enemy Turret Class
	int32 LoopIndex = 0;
	while (LoopIndex < EnemyTurretCount) {
		AActor* EnemyTurretActor = EnmyTurret[LoopIndex];

		AEnemyTurret* EnmyTurtRef = Cast<AEnemyTurret>(EnemyTurretActor);
		if (EnmyTurtRef && Tank) {
			EnmyTurtRef->Tank = Tank;
		}
		LoopIndex++;
	}

	//Creating UI Widget To Display Messages On Screen
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController) {
		ScreenMessageWidget = CreateWidget<UScreenMessage>(PlayerController, ScreenMessageClass);
		if (ScreenMessageWidget) {
			ScreenMessageWidget->AddToPlayerScreen();
		}
	}

	//Setting Level Start Countdown Timer
	CountdownSeconds = CountdownDelay;
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ABattleBlasterGameMode::OnCountdownTimerTimeout, 1.0f, true);
}

void ABattleBlasterGameMode::OnCountdownTimerTimeout()
{
	//Case Where CountDown Timer Is Greater Than Zero
	if (CountdownSeconds > 0) {
		FString Message = FString::Printf(TEXT("Level Starts In: %d"), CountdownSeconds);
		ScreenMessageWidget->SetMessageText(Message);
	}
	//Case Where CountDown Timer Is Equal To Zero
	else if (CountdownSeconds == 0) {
		ScreenMessageWidget->SetMessageText("GO!!!");
		Tank->SetPlayerEnabled(true);
	}
	//Case Where CountDown Timer Is Less Than Zero
	else {
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		ScreenMessageWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	CountdownSeconds--;
}

void ABattleBlasterGameMode::ActorDied(AActor* DeadActor)
{
	bool IsGameOver = false;

	//Player Dead Case
	if (DeadActor == Tank) {
		Tank->HandleDestruction();//Player Dead Function Call
		IsGameOver = true;
	}
	//Enemy Turrets Dead Case
	else
	{
		AEnemyTurret* DeadEnemyTurret = Cast<AEnemyTurret>(DeadActor);
		if (DeadEnemyTurret) {
			DeadEnemyTurret->HandleDestruction();//Enemy Turret Dead Function Call

			EnemyTurretCount -= 1;
			if (EnemyTurretCount <= 0) {
				IsGameOver = true;
				IsVictory = true;
			}
		}
	}

	//Handling GameOver State Based On IsGameOver and IsVictory variables
	if (IsGameOver) {
		FString GameOverString = IsVictory ? "Victory" : "Defeat!";
		ScreenMessageWidget->SetVisibility(ESlateVisibility::Visible);
		ScreenMessageWidget->SetMessageText(GameOverString);

		//Setting Timer To Call LoadNextLevel or RestartCurrentLevel With Some Delay
		FTimerHandle GameOverTimerHandle;
		GetWorldTimerManager().SetTimer(GameOverTimerHandle, this, &ABattleBlasterGameMode::OnGameOverTimerTimeout, GameOverDelay, false);
	}
}

void ABattleBlasterGameMode::OnGameOverTimerTimeout()
{
	//Getting GameInstance Class Reference To Call LoadNextLevel or RestartCurrentLevel Functions
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

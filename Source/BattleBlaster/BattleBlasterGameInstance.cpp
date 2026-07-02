// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameInstance.h"

#include "Kismet/GameplayStatics.h"

//Function To Load Next Level or Curret Level Again
void UBattleBlasterGameInstance::ChangeLevel(int32 Index)
{
	if (Index > 0 && Index <= LastLevelIndex) {
		CurrentLevelIndex = Index;

		FString LevelNameString = FString::Printf(TEXT("Level_%d"), CurrentLevelIndex);
		//Loading Next Level
		UGameplayStatics::OpenLevel(GetWorld(), *LevelNameString);
	}
}

//Function To Load Next Level Or Restart Game
void UBattleBlasterGameInstance::LoadNextLevel() {
	if (CurrentLevelIndex < LastLevelIndex) {
		//Loading Next Level Call
		ChangeLevel(CurrentLevelIndex + 1);
	}
	else {
		//Restarting Game Call
		RestartGame();
	}
}

//Function To Restart Current Level On Game Lose
void UBattleBlasterGameInstance::RestartCurrentLevel() {
	ChangeLevel(CurrentLevelIndex);
}

//Function To Restart Game On Game End
void UBattleBlasterGameInstance::RestartGame() {
	ChangeLevel(1);
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "GameStates/G_RaceGameState.h"
#include <GameModes/G_RaceGameMode.h>
#include <Kismet/GameplayStatics.h>
#include <Player/G_RacePlayerController.h>
#include "Net/UnrealNetwork.h"


AG_RaceGameState::AG_RaceGameState()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AG_RaceGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AG_RaceGameState, bAnyPlayerFinished);
    DOREPLIFETIME(AG_RaceGameState, Timer);
}

void AG_RaceGameState::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bAnyPlayerFinished)
    {
        UpdateTimer(DeltaTime);
    }
}

void AG_RaceGameState::AddFinishedPlayer(AG_RacePlayerController* PlayerController)
{
    FinishedPlayersCount++;
    OnPlayerFinishRace.Broadcast(PlayerController, FinishedPlayersCount);

    if (!bAnyPlayerFinished)
    {
        bAnyPlayerFinished = true;
    }
}

void AG_RaceGameState::UpdateTimer(float DeltaTime)
{
    Timer += DeltaTime;
    RaceGameMode = RaceGameMode ? RaceGameMode : GetDefaultGameMode<AG_RaceGameMode>();
    if (!RaceGameMode) return;

    float TimeLimit = RaceGameMode->GetTimeLimit();
    OnTimerUpdate.Broadcast(TimeLimit - Timer);
}

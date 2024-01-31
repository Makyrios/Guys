// Fill out your copyright notice in the Description page of Project Settings.

#include "GameStates/G_LobbyGameState.h"
#include <Net/UnrealNetwork.h>
#include <GameModes/G_LobbyGameMode.h>

AG_LobbyGameState::AG_LobbyGameState()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AG_LobbyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AG_LobbyGameState, Timer);
}

void AG_LobbyGameState::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bMinPlayersReached)
    {
        UpdateTimer(DeltaTime);
    }
}

void AG_LobbyGameState::UpdateTimer(float DeltaTime)
{
    Timer += DeltaTime;
    LobbyGameMode = LobbyGameMode ? LobbyGameMode : GetDefaultGameMode<AG_LobbyGameMode>();
    if (!LobbyGameMode) return;

    float TimeLimit = LobbyGameMode->GetChangeMapDelay();
    OnTimerUpdate.Broadcast(TimeLimit - Timer);
}

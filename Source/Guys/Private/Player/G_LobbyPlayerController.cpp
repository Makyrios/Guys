// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/G_LobbyPlayerController.h"
#include <UI/HUD/G_LobbyHUD.h>
#include <GameStates/G_LobbyGameState.h>

void AG_LobbyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    AG_LobbyGameState* LobbyGameState = GetWorld()->GetGameState<AG_LobbyGameState>();
    if (LobbyGameState)
    {
        LobbyGameState->OnTimerUpdate.AddUObject(this, &AG_LobbyPlayerController::OnTimerUpdate);
        LobbyGameState->OnPlayersUpdate.AddUObject(this, &AG_LobbyPlayerController::OnPlayersUpdate);
    }
}

void AG_LobbyPlayerController::OnTimerUpdate(float RemainingSeconds)
{
    if (!IsLocalController())
    {
        Client_SetTimeRemaining(RemainingSeconds);
        return;
    }

    LobbyHUD = (!LobbyHUD) ? GetHUD<AG_LobbyHUD>() : LobbyHUD;
    if (!LobbyHUD) return;

    LobbyHUD->SetTimeRemaining(RemainingSeconds);
}

void AG_LobbyPlayerController::Client_SetTimeRemaining_Implementation(float RemainingSeconds)
{
    OnTimerUpdate(RemainingSeconds);
}

void AG_LobbyPlayerController::OnPlayersUpdate(int ConnectedPlayers, int DesiredPlayersNum)
{
    if (!IsLocalController())
    {
        Client_SetPlayersText(ConnectedPlayers, DesiredPlayersNum);
        return;
    }

    LobbyHUD = (!LobbyHUD) ? GetHUD<AG_LobbyHUD>() : LobbyHUD;
    if (!LobbyHUD) return;

    LobbyHUD->SetPlayersText(ConnectedPlayers, DesiredPlayersNum);
}

void AG_LobbyPlayerController::Client_SetPlayersText_Implementation(int ConnectedPlayers, int DesiredPlayersNum)
{
    OnPlayersUpdate(ConnectedPlayers, DesiredPlayersNum);
}

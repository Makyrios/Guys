// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/G_RacePlayerController.h"
#include <UI/HUD/G_RaceHUD.h>
#include <GameStates/G_RaceGameState.h>
#include <GameModes/G_RaceGameMode.h>
#include <Kismet/GameplayStatics.h>
#include <Components/SlateWrapperTypes.h>

void AG_RacePlayerController::BeginPlay()
{
    Super::BeginPlay();

    AG_RaceGameState* RaceGameState = GetWorld()->GetGameState<AG_RaceGameState>();
    if (RaceGameState)
    {
        RaceGameState->OnTimerUpdate.AddUObject(this, &AG_RacePlayerController::OnTimerUpdate);
    }
}


void AG_RacePlayerController::HandleFinishRace()
{
    if (!IsLocalController())
    {
        Client_HandleFinishRace();
        return;
    }

    RaceHUD = (!RaceHUD) ? GetHUD<AG_RaceHUD>() : RaceHUD;
    if (!RaceHUD) return;

    RaceHUD->ShowFinishRaceWidget();
}

void AG_RacePlayerController::Client_HandleFinishRace_Implementation()
{
    RaceHUD = (!RaceHUD) ? GetHUD<AG_RaceHUD>() : RaceHUD;
    if (!RaceHUD) return;

    RaceHUD->ShowFinishRaceWidget();
}

void AG_RacePlayerController::HandleWinRace(int32 Place)
{
    if (!IsLocalController())
    {
        Client_HandleWinRace(Place);
        return;
    }

    RaceHUD = (!RaceHUD) ? GetHUD<AG_RaceHUD>() : RaceHUD;
    if (!RaceHUD) return;

    RaceHUD->ShowWinRaceWidget(Place);
}

void AG_RacePlayerController::Client_HandleWinRace_Implementation(int32 Place)
{
    HandleWinRace(Place);
}

void AG_RacePlayerController::SetPlayerPosition(int32 Position)
{
    if (!IsLocalController())
    {
        Client_SetPlayerPosition(Position);
        return;
    }

    RaceHUD = (!RaceHUD) ? GetHUD<AG_RaceHUD>() : RaceHUD;
    if (!RaceHUD) return;

    RaceHUD->SetPlayerPosition(Position);
}

void AG_RacePlayerController::Client_SetPlayerPosition_Implementation(int32 Position)
{
    //SetPlayerPosition(Position);
    RaceHUD = (!RaceHUD) ? GetHUD<AG_RaceHUD>() : RaceHUD;
    if (!RaceHUD) return;

    RaceHUD->SetPlayerPosition(Position);
}

void AG_RacePlayerController::OnTimerUpdate(float RemainingSeconds)
{
    if (!IsLocalController())
    {
        Client_SetTimeRemaining(RemainingSeconds);
        return;
    }

    RaceHUD = (!RaceHUD) ? GetHUD<AG_RaceHUD>() : RaceHUD;
    if (!RaceHUD) return;

    RaceHUD->SetTimeRemaining(RemainingSeconds);
}

void AG_RacePlayerController::Client_SetTimeRemaining_Implementation(float RemainingSeconds)
{
    RaceHUD = (!RaceHUD) ? GetHUD<AG_RaceHUD>() : RaceHUD;
    if (!RaceHUD) return;

    RaceHUD->SetTimeRemaining(RemainingSeconds);
}

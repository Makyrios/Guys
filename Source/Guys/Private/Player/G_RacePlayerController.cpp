// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/G_RacePlayerController.h"
#include <UI/HUD/G_RaceHUD.h>
#include <GameStates/G_RaceGameState.h>
#include <GameModes/G_RaceGameMode.h>
#include <Kismet/GameplayStatics.h>

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

void AG_RacePlayerController::HandleWinRace()
{
    if (!IsLocalController())
    {
        Client_HandleWinRace();
        return;
    }

    RaceHUD = (!RaceHUD) ? GetHUD<AG_RaceHUD>() : RaceHUD;
    if (!RaceHUD) return;

    RaceHUD->ShowWinRaceWidget();
}

void AG_RacePlayerController::Client_HandleWinRace_Implementation()
{
	RaceHUD = (!RaceHUD) ? GetHUD<AG_RaceHUD>() : RaceHUD;
	if (!RaceHUD) return;

	RaceHUD->ShowWinRaceWidget();
}

void AG_RacePlayerController::BeginPlay()
{
    Super::BeginPlay();

    AG_RaceGameState* RaceGameState = GetWorld()->GetGameState<AG_RaceGameState>();
    if (RaceGameState)
    {
        RaceGameState->OnTimerUpdate.AddUObject(this, &AG_RacePlayerController::OnTimerUpdate);
    }
}

void AG_RacePlayerController::OnTimerUpdate(float RemainingSeconds)
{
    if (HasAuthority() && IsLocalController())
    {
        RaceHUD = (!RaceHUD) ? GetHUD<AG_RaceHUD>() : RaceHUD;
        if (!RaceHUD) return;

        RaceHUD->SetTimeRemaining(RemainingSeconds);
    }
    else
    {
        Client_SetTimeRemaining(RemainingSeconds);
    }
}

void AG_RacePlayerController::Client_SetTimeRemaining_Implementation(float RemainingSeconds)
{
    RaceHUD = (!RaceHUD) ? GetHUD<AG_RaceHUD>() : RaceHUD;
    if (!RaceHUD) return;

    RaceHUD->SetTimeRemaining(RemainingSeconds);
}


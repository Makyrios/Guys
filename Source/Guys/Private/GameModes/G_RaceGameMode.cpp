// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/G_RaceGameMode.h"

bool AG_RaceGameMode::ReadyToEndMatch_Implementation()
{

    /* TODO
    if (const AG_RaceGameState* CurrentGameState = Cast<AG_RaceGameState>(GameState))
    {
        return CurrentGameState->GetWinner() != nullptr || Super::ReadyToEndMatch_Implementation();
    }*/
    return false;
}

void AG_RaceGameMode::HandleMatchHasEnded()
{
    Super::HandleMatchHasEnded();

    
    /* TODO
    const AAS_DeathmatchGameState* CustomGameState = GetGameState<AAS_DeathmatchGameState>();
    if (!CustomGameState) return;

    const AController* WonController = CustomGameState->GetWinningPlayer();
    if (!WonController) return;

    for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
    {
        AAS_PlayerController* CustomController = Cast<AAS_PlayerController>(*Iterator);
        if (CustomController && (*Iterator).Get() == WonController)
        {
            CustomController->HandleWin();
        }
        else
        {
            CustomController->HandleLose();
        }
    }*/
}

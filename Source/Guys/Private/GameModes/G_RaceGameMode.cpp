// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/G_RaceGameMode.h"
#include <Player/G_PlayerState.h>
#include "Actors/G_Checkpoint.h"
#include <Character/G_Character.h>

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

void AG_RaceGameMode::RespawnPawn(AController* Controller)
{
    if (!Controller) return;
    APawn* OldPawn = Controller->GetPawn();
    APawn* NewPawn = GetSpawnedPawn(OldPawn);

    OldPawn->Destroy();
    if (NewPawn)
    {
        Controller->UnPossess();
        Controller->Possess(NewPawn);
    }
}

APawn* AG_RaceGameMode::GetSpawnedPawn(APawn* OldPawn) const
{
    UWorld* World = GetWorld();
    AG_PlayerState* PlayerState = OldPawn->GetPlayerState<AG_PlayerState>();
    AG_Checkpoint* LastCheckpoint = PlayerState->GetLastCheckpoint().Get();
    if (!World || !OldPawn || !PlayerState || !LastCheckpoint) return nullptr;

    FVector RespawnLocation = LastCheckpoint->GetRandomSpawnPoint();
    APawn* NewPawn = World->SpawnActor<APawn>(OldPawn->GetClass(), RespawnLocation, LastCheckpoint->GetActorRightVector().Rotation());

    /*Find new spawn location if previous is occupied*/
    while (NewPawn == nullptr)
    {
        RespawnLocation = LastCheckpoint->GetRandomSpawnPoint();
        NewPawn = World->SpawnActor<APawn>(OldPawn->GetClass(), RespawnLocation, LastCheckpoint->GetActorRightVector().Rotation());
    }

    return NewPawn;
}

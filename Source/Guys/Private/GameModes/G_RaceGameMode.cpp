// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/G_RaceGameMode.h"
#include <Player/G_RacePlayerState.h>
#include "Actors/G_Checkpoint.h"
#include <Character/G_Character.h>
#include <GameStates/G_RaceGameState.h>
#include "Player/G_RacePlayerController.h"
#include "GameFramework/SpectatorPawn.h"


void AG_RaceGameMode::BeginPlay()
{
    Super::BeginPlay();

    if (AG_RaceGameState* RaceGameState = GetGameState<AG_RaceGameState>())
    {
		RaceGameState->OnPlayerFinishRace.AddUObject(this, &AG_RaceGameMode::OnPlayerFinishRace);
	}
}

bool AG_RaceGameMode::ReadyToEndMatch_Implementation()
{
    if (const AG_RaceGameState* CurrentGameState = Cast<AG_RaceGameState>(GameState))
    {
        return CurrentGameState->GetTimer() >= TimeLimit 
            || CurrentGameState->GetFinishedPlayersCount() == CurrentGameState->PlayerArray.Num() 
            || Super::ReadyToEndMatch_Implementation();
    }
    return false;
}

void AG_RaceGameMode::HandleMatchHasEnded()
{
    Super::HandleMatchHasEnded();

    for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
    {
        AG_RacePlayerController* RaceController = Cast<AG_RacePlayerController>(*Iterator);
        if (RaceController)
        {
            RaceController->HandleFinishRace();
        }
    }
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

void AG_RaceGameMode::OnPlayerFinishRace(AG_RacePlayerController* RaceController, int32 Place)
{
    if (!RaceController) return;

    AG_RacePlayerState* PlayerState = RaceController->GetPlayerState<AG_RacePlayerState>();
    if (PlayerState)
    {
        PlayerState->SetFinishedRace(true);
    }

	RaceController->HandleWinRace(Place);
    
    SpawnSpectatorPawn(RaceController);
}

APawn* AG_RaceGameMode::GetSpawnedPawn(APawn* OldPawn) const
{
    UWorld* World = GetWorld();
    AG_RacePlayerState* PlayerState = OldPawn->GetPlayerState<AG_RacePlayerState>();
    AG_Checkpoint* LastCheckpoint = PlayerState->GetLastCheckpoint().Get();
    if (!World || !OldPawn || !PlayerState || !LastCheckpoint) return nullptr;

    FVector RespawnLocation = LastCheckpoint->GetRandomSpawnPoint();
    APawn* NewPawn = World->SpawnActor<APawn>(OldPawn->GetClass(), RespawnLocation, LastCheckpoint->GetActorRotation());

    /*Find new spawn location if previous is occupied*/
    while (NewPawn == nullptr)
    {
        RespawnLocation = LastCheckpoint->GetRandomSpawnPoint();
        NewPawn = World->SpawnActor<APawn>(OldPawn->GetClass(), RespawnLocation, LastCheckpoint->GetActorRotation());
    }

    return NewPawn;
}

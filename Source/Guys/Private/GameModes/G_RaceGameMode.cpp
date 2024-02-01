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

void AG_RaceGameMode::HandleSeamlessTravelPlayer(AController*& C)
{
    Super::HandleSeamlessTravelPlayer(C);
}

bool AG_RaceGameMode::ReadyToEndMatch_Implementation()
{
    if (const AG_RaceGameState* CurrentGameState = Cast<AG_RaceGameState>(GameState))
    {
        return CurrentGameState->GetTimer() >= TimeLimit ||
               CurrentGameState->GetFinishedPlayersCount() == CurrentGameState->PlayerArray.Num() ||
               Super::ReadyToEndMatch_Implementation();
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

void AG_RaceGameMode::HandleLoginBeforeGameStart(APlayerController* NewPlayer)
{
    SpawnNewPawn(NewPlayer);
}

void AG_RaceGameMode::HandleLoginAfterGameStart(APlayerController* NewPlayer)
{
    SpawnSpectatorPawn(NewPlayer);
    EnableSpectatorHUD(NewPlayer);
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

APawn* AG_RaceGameMode::SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot)
{
    return nullptr;
}

void AG_RaceGameMode::OnAllPlayersLoaded()
{
    Super::OnAllPlayersLoaded();

    for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
    {
        if (Iterator)
        {
            CreateStartGameWidget(Iterator->Get());
        }
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

APawn* AG_RaceGameMode::GetSpawnedPawn(APawn* OldPawn)
{
    AG_RacePlayerState* PlayerState = OldPawn->GetPlayerState<AG_RacePlayerState>();
    AG_Checkpoint* LastCheckpoint = PlayerState->GetLastCheckpoint().Get();
    if (!OldPawn || !PlayerState) return nullptr;

    if (LastCheckpoint)
    {
        APawn* SpawnedPawn = SpawnPawnAtLocation(LastCheckpoint->GetRandomSpawnPoint(), LastCheckpoint->GetActorRotation(), OldPawn);
        int Tries = 0;
        while (!SpawnedPawn && Tries <= 5)
        {
            SpawnedPawn = SpawnPawnAtLocation(LastCheckpoint->GetRandomSpawnPoint(), LastCheckpoint->GetActorRotation(), OldPawn);
            Tries += 1;
        }
        return SpawnedPawn;
    }
    // If checkpoint is null spawn at player start
    else
    {
        AActor* PlayerStart = ChoosePlayerStart(OldPawn->GetController());
        if (PlayerStart)
        {
            APawn* SpawnedPawn = SpawnPawnAtLocation(PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation(), OldPawn);
            int Tries = 0;
            while (!SpawnedPawn && Tries <= 5)
            {
                PlayerStart = ChoosePlayerStart(OldPawn->GetController());
                if (!PlayerStart) continue;
                SpawnedPawn = SpawnPawnAtLocation(PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation(), OldPawn);
                Tries += 1;
            }
            return SpawnedPawn;
        }
    }

    return nullptr;
}

APawn* AG_RaceGameMode::SpawnPawnAtLocation(FVector SpawnLocation, FRotator SpawnRotation, APawn* OldPawn)
{
    APawn* NewPawn = GetWorld()->SpawnActor<APawn>(OldPawn->GetClass(), SpawnLocation, SpawnRotation);
    return NewPawn;
}
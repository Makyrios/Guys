// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/G_Checkpoint_FinishLine.h"
#include <Kismet/GameplayStatics.h>
#include <GameStates/G_RaceGameState.h>
#include "Player/G_RacePlayerController.h"
#include <Player/G_RacePlayerState.h>


void AG_Checkpoint_FinishLine::HandleCheckpointOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AddPointsToPlayer(OtherActor);

    HandleFinishingRace(OtherActor);
}

void AG_Checkpoint_FinishLine::AddPointsToPlayer(AActor* OtherActor)
{
    if (APawn* Pawn = Cast<APawn>(OtherActor))
    {
        if (AG_RacePlayerState* PlayerState = Pawn->GetPlayerState<AG_RacePlayerState>())
        {
            PlayerState->AddPlayerScore(Points);
            Points -= RemovePointsPerPlayer;
        }
    }
}

void AG_Checkpoint_FinishLine::HandleFinishingRace(AActor* OtherActor)
{
    if (AG_RacePlayerController* RaceController = OtherActor->GetInstigatorController<AG_RacePlayerController>())
    {
        if (AG_RaceGameState* GameState = Cast<AG_RaceGameState>(UGameplayStatics::GetGameState(this)))
        {
            GameState->AddFinishedPlayer(RaceController);
        }
        OtherActor->Destroy();
    }
}

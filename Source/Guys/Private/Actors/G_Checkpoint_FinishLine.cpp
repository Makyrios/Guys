// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/G_Checkpoint_FinishLine.h"
#include <Kismet/GameplayStatics.h>

void AG_Checkpoint_FinishLine::HandleCheckpointOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    Super::HandleCheckpointOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
    /* TODO
    if (AG_RaceGameState* GameState = Cast<AG_RaceGameState>(UGameplayStatics::GetGameState(this)) 
    {
        GameState->SetWinner(OtherActor);
    }
    */
}

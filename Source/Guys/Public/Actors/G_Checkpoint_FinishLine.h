// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/G_Checkpoint.h"
#include "G_Checkpoint_FinishLine.generated.h"

/**
 *
 */
UCLASS()
class GUYS_API AG_Checkpoint_FinishLine : public AG_Checkpoint
{
    GENERATED_BODY()

protected:
    virtual void HandleCheckpointOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

    void HandleFinishingRace(AActor* OtherActor);

    void AddPointsToPlayer(AActor* OtherActor);

private:
    UPROPERTY(EditAnywhere, Category = "G|Checkpoint")
    int RemovePointsPerPlayer = 5;
};

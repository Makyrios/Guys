// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/G_PlayerState.h"
#include "G_RacePlayerState.generated.h"

UCLASS()
class GUYS_API AG_RacePlayerState : public AG_PlayerState
{
    GENERATED_BODY()

public:
    FORCEINLINE void AddPlayerScore(int32 ScoreToAdd) { PlayerScore += ScoreToAdd; }
    FORCEINLINE int32 GetPlayerScore() const { return PlayerScore; }

    FORCEINLINE void SetLastCheckpoint(TWeakObjectPtr<AG_Checkpoint> Checkpoint) { LastCheckpoint = Checkpoint; }
    FORCEINLINE TWeakObjectPtr<AG_Checkpoint> GetLastCheckpoint() const { return LastCheckpoint; }

    FORCEINLINE void SetFinishedRace(bool bFinished) { bFinishedRace = bFinished; }
    FORCEINLINE bool GetFinishedRace() const { return bFinishedRace; }

protected:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
    UPROPERTY(Replicated, VisibleAnywhere, Category = "G|Stats")
    int32 PlayerScore = 0;

    UPROPERTY(Replicated, VisibleAnywhere, Category = "G|Spawn")
    TWeakObjectPtr<AG_Checkpoint> LastCheckpoint;

    bool bFinishedRace = false;
};

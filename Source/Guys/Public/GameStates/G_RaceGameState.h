// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "G_RaceGameState.generated.h"

class AG_RacePlayerController;
class AG_RaceGameMode;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerUpdate, float);

UCLASS()
class GUYS_API AG_RaceGameState : public AGameState
{
    GENERATED_BODY()

public:
    AG_RaceGameState();
    virtual void Tick(float DeltaTime) override;

    /*
    void AddFinishedPlayerController(TWeakPtr<AG_RacePlayerController> PlayerController);
    */
    void AddFinishedPlayer();

    FORCEINLINE float GetTimer() const { return Timer; }

public:
    FOnTimerUpdate OnTimerUpdate;

private:
    void UpdateTimer(float DeltaTime);

private:
    UPROPERTY()
    const AG_RaceGameMode* RaceGameMode;

    int FinishedPlayersCount = 0;

    bool bAnyPlayerFinished = false;

    float Timer = 0.f;
    /*UPROPERTY()
    TArray<TWeakPtr<AG_RacePlayerController>> FinishedPlayerControllers;*/
};

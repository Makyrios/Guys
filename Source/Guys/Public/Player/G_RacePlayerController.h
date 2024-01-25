// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/G_PlayerController.h"
#include "G_RacePlayerController.generated.h"

class AG_RaceHUD;
class ASpectatorPawn;

UCLASS()
class GUYS_API AG_RacePlayerController : public AG_PlayerController
{
    GENERATED_BODY()

public:
    void HandleFinishRace();

    void HandleWinRace();

protected:
    virtual void BeginPlay() override;

private:
    void OnTimerUpdate(float RemainingSeconds);

    UFUNCTION(Client, Unreliable)
    void Client_SetTimeRemaining(float RemainingSeconds);

    UFUNCTION(Client, Reliable)
    void Client_HandleFinishRace();

    UFUNCTION(Client, Reliable)
    void Client_HandleWinRace();

private:
    UPROPERTY()
    TObjectPtr<AG_RaceHUD> RaceHUD;

};

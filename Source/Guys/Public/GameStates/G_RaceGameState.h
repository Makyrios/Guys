// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "G_RaceGameState.generated.h"

class AG_RacePlayerController;
class AG_RaceGameMode;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlayerFinishRace, AG_RacePlayerController*, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerUpdate, float);

UCLASS()
class GUYS_API AG_RaceGameState : public AGameState
{
    GENERATED_BODY()

public:
    AG_RaceGameState();
    virtual void Tick(float DeltaTime) override;

    void AddFinishedPlayer(AG_RacePlayerController* PlayerController);

    FORCEINLINE float GetTimer() const { return Timer; }
    FORCEINLINE int GetFinishedPlayersCount() const { return FinishedPlayersCount; }

    FORCEINLINE void SetPlayerProgressesMap(TMap<AActor*, float>& NewPlayerProgressesMap) { PlayerProgressesMap = NewPlayerProgressesMap; }
    FORCEINLINE const TMap<AActor*, float> GetPlayerProgressesMap() const { return PlayerProgressesMap; }

protected:
    void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
    void UpdateTimer(float DeltaTime);

public:
    FOnPlayerFinishRace OnPlayerFinishRace;
    FOnTimerUpdate OnTimerUpdate;

    UPROPERTY(BlueprintReadOnly)
    TMap<AActor*, float> PlayerProgressesMap;

private:
    UPROPERTY()
    const AG_RaceGameMode* RaceGameMode;

    int32 FinishedPlayersCount = 0;

    UPROPERTY(Replicated)
    bool bAnyPlayerFinished = false;
    UPROPERTY(Replicated)
    float Timer = 0.f;

};

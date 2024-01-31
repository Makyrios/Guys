// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "G_LobbyGameState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerUpdate, float);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlayersUpdate, int, int);


class AG_LobbyGameMode;

UCLASS()
class GUYS_API AG_LobbyGameState : public AGameState
{
    GENERATED_BODY()

public:
    AG_LobbyGameState();

    FORCEINLINE void SetMinPlayersReached(bool bReached) { bMinPlayersReached = bReached; }

protected:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void Tick(float DeltaTime) override;

private:
    void UpdateTimer(float DeltaTime);

    void UpdatePlayers(int ConnectedPlayers, int DesiredPlayersNum);

public:
    FOnTimerUpdate OnTimerUpdate;
    FOnPlayersUpdate OnPlayersUpdate;

private:
    UPROPERTY()
    const AG_LobbyGameMode* LobbyGameMode;

    bool bMinPlayersReached = false;

    UPROPERTY(Replicated)
    float Timer = 0.f;
};

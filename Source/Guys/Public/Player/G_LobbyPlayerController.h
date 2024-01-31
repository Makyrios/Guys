// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/G_PlayerController.h"
#include "G_LobbyPlayerController.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerUpdate, float);

class AG_LobbyHUD;

UCLASS()
class GUYS_API AG_LobbyPlayerController : public AG_PlayerController
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

private:
    void OnTimerUpdate(float RemainingSeconds);

    UFUNCTION(Client, Unreliable)
    void Client_SetTimeRemaining(float RemainingSeconds);

    UPROPERTY()
    TObjectPtr<AG_LobbyHUD> LobbyHUD;
};

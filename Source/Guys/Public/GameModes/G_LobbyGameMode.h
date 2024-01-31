// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/G_BaseGameMode.h"
#include "G_LobbyGameMode.generated.h"

class APlayerController;
class UMultiplayerSubsystem;

UCLASS()
class GUYS_API AG_LobbyGameMode : public AG_BaseGameMode
{
    GENERATED_BODY()

public:
    FORCEINLINE float GetChangeMapDelay() const { return ChangeMapDelay; }

protected:
    virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

    virtual void PostLogin(APlayerController* NewPlayer) override;

    void OnMinPlayersReached();

    void StartChangeMapTimer(UMultiplayerSubsystem* Subsystem);

private:
    void ChangeMap(UMultiplayerSubsystem* Subsystem);

    int32 GetNumExpectedPlayers() const;

public:
    UPROPERTY(EditAnywhere, Category = "G|Maps")
    TMap<FString, FString> MapsForModes;

    UPROPERTY(EditAnywhere, Category = "G|Maps")
    float ChangeMapDelay = 10.f;
};

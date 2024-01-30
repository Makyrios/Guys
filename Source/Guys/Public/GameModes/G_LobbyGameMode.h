// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/G_BaseGameMode.h"
#include "G_LobbyGameMode.generated.h"

UCLASS()
class GUYS_API AG_LobbyGameMode : public AG_BaseGameMode
{
    GENERATED_BODY()

protected:
    virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

    virtual void HandleLoginAfterGameStart(APlayerController* NewPlayer) override;


private:
    void MapChange(FName MapName);

    int32 GetNumExpectedPlayers() const;

};

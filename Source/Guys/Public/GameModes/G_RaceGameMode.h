// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/G_BaseGameMode.h"
#include "G_RaceGameMode.generated.h"

class AG_RacePlayerController;

UCLASS()
class GUYS_API AG_RaceGameMode : public AG_BaseGameMode
{
    GENERATED_BODY()

public:
    APawn* GetSpawnedPawn(APawn* OldPawn) const;

    FORCEINLINE float GetTimeLimit() const { return TimeLimit; }

protected:
    virtual void BeginPlay() override;
    virtual bool ReadyToEndMatch_Implementation() override;
    virtual void HandleMatchHasEnded() override;
    virtual void RespawnPawn(AController* Controller) override;

private:
    UFUNCTION()
    void OnPlayerFinishRace(AG_RacePlayerController* RaceController, int32 Place);

private:
    UPROPERTY(EditDefaultsOnly, Category = "G|Gameplay")
    float TimeLimit = 180;
};

// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "G_BaseGameMode.generated.h"

UCLASS(minimalapi)
class AG_BaseGameMode : public AGameMode
{
    GENERATED_BODY()

public:
    virtual void HandleActorDeath(AController* DeadActor);

    FORCEINLINE float GetTimeLimit() const { return TimeLimit; }
    FORCEINLINE float GetDelayBeforeStart() const { return DelayBeforeStart; }
    virtual bool IsGameStarted();

    UFUNCTION()
    virtual void RespawnPawn(AController* Controller);

protected:
    virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
    virtual void PostLogin(APlayerController* NewPlayer) override;
    virtual void HandleMatchHasStarted() override;
    AActor* ChoosePlayerStart_Implementation(AController* Player) override;
    virtual bool ReadyToStartMatch_Implementation() override;
    virtual bool ReadyToEndMatch_Implementation() override;
    virtual void HandleMatchHasEnded() override;

private:
    void CreateStartGameWidget(APlayerController* NewPlayer);
    void RestartGame();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "G|GameStart", meta = (EditCondition = "bDelayedStart"))
    float DelayBeforeStart;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "G|Gameplay")
    float TimeLimit;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "G|GameEnd")
    float DelayBeforeRestart;

    UPROPERTY()
    FTimerHandle DelayStartTimer;
    FTimerDelegate RespawnDelegate;
};

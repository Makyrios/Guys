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
    FORCEINLINE float GetDelayBeforeStart() const { return DelayBeforeStart; }

    UFUNCTION()
    virtual void RespawnPawn(AController* Controller);

protected:
    virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
    virtual bool IsGameStarted();
    virtual void PostLogin(APlayerController* NewPlayer) override;
    virtual void HandleMatchIsWaitingToStart() override;
    virtual void HandleMatchHasStarted() override;
    virtual void HandleMatchHasEnded() override;
    virtual void HandleActorDeath(AController* DeadActor);
    virtual bool ReadyToStartMatch_Implementation() override;
    virtual bool ReadyToEndMatch_Implementation() override;
    virtual APawn* SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot) override;

private:
    AActor* ChoosePlayerStart();
    void ShowHUDWidget(APlayerController* PlayerController);
    void SetControllerMatchState(APlayerController* PlayerController, FName NewMatchState);
    void MovePawnToRandomPlayerStart(APawn* PawnToMove);
    void CreateStartGameWidget(APlayerController* NewPlayer);
    void RestartGame();
    bool IsMatchStarted();
    bool IsMatchPreparing();
    void HandleLoginBeforeGameStart(APlayerController* NewPlayer);
    void HandleLoginAfterGameStart(APlayerController* NewPlayer);
    void EnableSpectatorHUD(APlayerController* NewPlayer);
    void SpawnNewPawn(APlayerController* NewPlayer);
    void SpawnSpectatorPawn(APlayerController* NewPlayer);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "G|GameStart", meta = (EditCondition = "bDelayedStart"))
    float DelayBeforeStart;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "G|GameEnd")
    float DelayBeforeRestart;

    UPROPERTY()
    FTimerHandle DelayStartTimer;
    FTimerDelegate RespawnDelegate;
};

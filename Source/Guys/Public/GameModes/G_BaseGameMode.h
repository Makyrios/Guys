// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "G_BaseGameMode.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnChangeMatchState, FName);

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
    void HandlePlayerLoad(APlayerController* NewPlayer);
    virtual void HandleMatchHasEnded() override;
    virtual void HandleSeamlessTravelPlayer(AController*& C) override;
    virtual void HandleActorDeath(AController* DeadActor);
    virtual bool ReadyToStartMatch_Implementation() override;
    virtual bool ReadyToEndMatch_Implementation() override;

    virtual void HandleLoginBeforeGameStart(APlayerController* NewPlayer);
    virtual void HandleLoginAfterGameStart(APlayerController* NewPlayer);
    virtual void OnAllPlayersLoaded();
    virtual int32 GetNumExpectedPlayers() const;

    virtual void SetMatchState(FName NewMatchState) override;

    void SpawnNewPawn(APlayerController* NewPlayer);
    void SpawnSpectatorPawn(APlayerController* NewPlayer);
    void SetControllerMatchState(APlayerController* PlayerController, FName NewMatchState);
    void EnableSpectatorHUD(APlayerController* NewPlayer);
    void CreateStartGameWidget(APlayerController* NewPlayer);
    AActor* ChooseRandomPlayerStart() const;

private:
    void ShowHUDWidget(APlayerController* PlayerController);
    void MovePawnToRandomPlayerStart(APawn* PawnToMove);
    void RestartGame();
    bool IsMatchStarted();
    bool IsMatchPreparing();
    void UpdatePlayerSkins() const;

public:
    FOnChangeMatchState OnChangeMatchState;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "G|Game", meta = (EditCondition = "bDelayedStart"))
    float DelayBeforeStart;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "G|Game")
    float DelayBeforeRestart;

    UPROPERTY()
    FTimerHandle DelayStartTimer;
    FTimerDelegate RespawnDelegate;

    int32 LoadedPlayers = 0;
};

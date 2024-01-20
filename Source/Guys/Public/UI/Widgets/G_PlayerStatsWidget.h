// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "G_PlayerStatsWidget.generated.h"

class AG_PlayerState;
class UTextBlock;
class UImage;

UCLASS()
class GUYS_API UG_PlayerStatsWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetPlayerState(AG_PlayerState* NewPlayerState);
    void SetPlayerName(FText PlayerName);
    void SetScore(int32 Score);
    void SetPing(int32 Ping);

protected:
    void NativeOnInitialized() override;

    void UpdatePlayerStats();

private:
    UPROPERTY(EditAnywhere, meta = (BindWidget))
    TObjectPtr<UTextBlock> PlayerNameText;

    UPROPERTY(EditAnywhere, meta = (BindWidget))
    TObjectPtr<UTextBlock> ScoreText;

    UPROPERTY(EditAnywhere, meta = (BindWidget))
    TObjectPtr<UTextBlock> PingText;

    UPROPERTY()
    TObjectPtr<AG_PlayerState> PlayerState;

    UPROPERTY()
    FTimerHandle UpdateTimer;

    float UpdateDelay = 0.2f;
};

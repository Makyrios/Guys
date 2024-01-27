// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/G_PlayerStatsWidget.h"
#include "Components/TextBlock.h"
#include "Player/G_RacePlayerState.h"

void UG_PlayerStatsWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    GetWorld()->GetTimerManager().SetTimer(UpdateTimer, this, &UG_PlayerStatsWidget::UpdatePlayerStats, UpdateDelay, true, 0.0f);
}

void UG_PlayerStatsWidget::UpdatePlayerStats()
{
    if (!PlayerState.IsValid()) return;

    FString PlayerName = PlayerState->GetPlayerName();
    int32 PlayerScore = PlayerState->GetPlayerScore();
    float PlayerPing = PlayerState->GetPingInMilliseconds();

    SetPlayerName(FText::FromString(PlayerName));
    SetScore(PlayerScore);
    SetPing(PlayerPing);
}

void UG_PlayerStatsWidget::SetPlayerState(AG_RacePlayerState* NewPlayerState)
{
    if (!NewPlayerState) return;
    PlayerState = NewPlayerState;
}

void UG_PlayerStatsWidget::SetPlayerName(FText PlayerName)
{
    PlayerNameText->SetText(PlayerName);
}

void UG_PlayerStatsWidget::SetScore(int32 Score)
{
    FString KillsString = FString::FromInt(Score);
    ScoreText->SetText(FText::FromString(KillsString));
}

void UG_PlayerStatsWidget::SetPing(int32 Ping)
{
    const FString PingString = FString::FromInt(Ping);
    PingText->SetText(FText::FromString(PingString));
}

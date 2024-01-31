// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/G_LobbyHUDWidget.h"
#include "UI/Widgets/G_TimerWidget.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"

void UG_LobbyHUDWidget::SetTimeRemaining(float RemainingSeconds)
{
    VerticalBox->SetVisibility(ESlateVisibility::Visible);
    Timer->SetTimerText(RemainingSeconds);
}

void UG_LobbyHUDWidget::SetPlayersText(int ConnectedPlayers, int DesiredPlayersNum)
{
    if (!PlayersText) return;
    if (ConnectedPlayers < DesiredPlayersNum)
    {
        PlayersText->SetVisibility(ESlateVisibility::Visible);

        FString PlayersString = FString::FromInt(ConnectedPlayers) + FString("/") + FString::FromInt(DesiredPlayersNum);
        PlayersText->SetText(FText::FromString(PlayersString));
    }
    else
    {
        PlayersText->SetVisibility(ESlateVisibility::Collapsed);
    }

}

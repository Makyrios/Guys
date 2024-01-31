// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/G_LobbyHUDWidget.h"
#include "UI/Widgets/G_TimerWidget.h"
#include "Components/VerticalBox.h"

void UG_LobbyHUDWidget::SetTimeRemaining(float RemainingSeconds)
{
    VerticalBox->SetVisibility(ESlateVisibility::Visible);
    Timer->SetTimerText(RemainingSeconds);
}

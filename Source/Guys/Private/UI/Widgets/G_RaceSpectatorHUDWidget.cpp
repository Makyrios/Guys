// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/G_RaceSpectatorHUDWidget.h"
#include <Kismet/KismetStringLibrary.h>
#include <Components/TextBlock.h>

void UG_RaceSpectatorHUDWidget::SetTimeText(float RemainingSeconds)
{
    if (!TimeText) return;

    if (TimeText->GetVisibility() != ESlateVisibility::Visible)
    {
        ShowTimer();
    }

    if (RemainingSeconds >= 0)
    {
        FString TimerString = UKismetStringLibrary::TimeSecondsToString(RemainingSeconds);
        TimerString.RemoveAt(5, 3);
        TimeText->SetText(FText::FromString(TimerString));
    }
}

void UG_RaceSpectatorHUDWidget::NativePreConstruct()
{
    SetVisibility(ESlateVisibility::Collapsed);
}

void UG_RaceSpectatorHUDWidget::ShowTimer()
{
    TimeText->SetVisibility(ESlateVisibility::Visible);
}

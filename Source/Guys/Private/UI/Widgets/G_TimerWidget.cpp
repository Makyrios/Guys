// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/G_TimerWidget.h"
#include "Components/TextBlock.h"
#include <Kismet/KismetStringLibrary.h>

void UG_TimerWidget::SetTimerText(float RemainingSeconds)
{
    if (!TimerText) return;

    if (TimerText->GetVisibility() != ESlateVisibility::Visible)
    {
        ShowTimer();
    }

    if (RemainingSeconds >= 0)
    {
        FString TimerString = UKismetStringLibrary::TimeSecondsToString(RemainingSeconds);
        TimerString.RemoveAt(5, 3);
        TimerText->SetText(FText::FromString(TimerString));
    }
}

void UG_TimerWidget::ShowTimer()
{
    TimerText->SetVisibility(ESlateVisibility::Visible);
}

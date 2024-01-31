// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/G_RaceSpectatorHUDWidget.h"
#include <Kismet/KismetStringLibrary.h>
#include <Components/TextBlock.h>
#include "UI/Widgets/G_TimerWidget.h"

void UG_RaceSpectatorHUDWidget::SetTimeText(float RemainingSeconds)
{
    Timer->SetTimerText(RemainingSeconds);
}

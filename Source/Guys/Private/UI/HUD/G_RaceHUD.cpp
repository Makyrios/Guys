// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/HUD/G_RaceHUD.h"
#include "UI/Widgets/G_RaceHUDWidget.h"
#include "Components/TextBlock.h"

void AG_RaceHUD::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    RaceHUDWidget = CreateWidget<UG_RaceHUDWidget>(GetOwningPlayerController(), RaceHUDWidgetClass);
    if (RaceHUDWidget)
    {
        RaceHUDWidget->AddToViewport();
        HUDWidget = RaceHUDWidget;
    }

}

void AG_RaceHUD::SetTimeRemaining(float RemainingSeconds)
{
    check(RaceHUDWidget);
    RaceHUDWidget->SetTimeText(RemainingSeconds);
}

void AG_RaceHUD::ShowTimer()
{
    check(RaceHUDWidget);
    RaceHUDWidget->ShowTimer();
}

void AG_RaceHUD::ShowFinishRaceWidget()
{
    UUserWidget* FinishRaceWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), FinishRaceWidgetClass);
    if (FinishRaceWidget)
    {
        FinishRaceWidget->AddToViewport();
    }
}

void AG_RaceHUD::ShowWinRaceWidget()
{
    UUserWidget* WinRaceWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), WinRaceWidgetClass);
    if (WinRaceWidget)
    {
        WinRaceWidget->AddToViewport();
    }
}

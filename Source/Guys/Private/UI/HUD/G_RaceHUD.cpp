// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/HUD/G_RaceHUD.h"
#include "UI/Widgets/G_RaceHUDWidget.h"
#include "Components/TextBlock.h"
#include "UI/Widgets/G_RaceSpectatorHUDWidget.h"

void AG_RaceHUD::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    RaceHUDWidget = CreateWidget<UG_RaceHUDWidget>(GetOwningPlayerController(), RaceHUDWidgetClass);
    if (RaceHUDWidget)
    {
        RaceHUDWidget->AddToViewport();
        HUDWidget = RaceHUDWidget;
    }

    RaceSpectatorHUDWidget = CreateWidget<UG_RaceSpectatorHUDWidget>(GetOwningPlayerController(), RaceSpectatorHUDWidgetClass);
    if (RaceSpectatorHUDWidget)
    {
        RaceSpectatorHUDWidget->AddToViewport();
        SpectatorHUDWidget = RaceSpectatorHUDWidget;
    }
}

void AG_RaceHUD::SetTimeRemaining(float RemainingSeconds)
{
    if (bIsSpectator)
    {
        if (RaceSpectatorHUDWidget)
        {
            RaceSpectatorHUDWidget->SetTimeText(RemainingSeconds);
        }
    }
    else
    {
        if (RaceHUDWidget)
        {
            RaceHUDWidget->SetTimeText(RemainingSeconds);
        }
    }
}

void AG_RaceHUD::ShowFinishRaceWidget()
{
    UUserWidget* FinishRaceWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), FinishRaceWidgetClass);
    if (FinishRaceWidget)
    {
        FinishRaceWidget->AddToViewport();
        SetHUDWidgetVisibility(ESlateVisibility::Collapsed);
        SetSpectatorHUDWidgetVisibility(ESlateVisibility::Collapsed);
    }
}

void AG_RaceHUD::ShowWinRaceWidget()
{
    UUserWidget* WinRaceWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), WinRaceWidgetClass);
    if (WinRaceWidget)
    {
        WinRaceWidget->AddToViewport();
        SetHUDWidgetVisibility(ESlateVisibility::Collapsed);
        SetSpectatorHUDWidgetVisibility(ESlateVisibility::Visible);
        bIsSpectator = true;
    }
}

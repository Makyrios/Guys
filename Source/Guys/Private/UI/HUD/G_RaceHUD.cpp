// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/HUD/G_RaceHUD.h"
#include "UI/Widgets/G_RaceHUDWidget.h"
#include "Components/TextBlock.h"
#include "UI/Widgets/G_RaceSpectatorHUDWidget.h"
#include <UI/Widgets/G_RaceWinWidget.h>
#include <UI/Widgets/G_RaceFinishWidget.h>
#include "Animation/WidgetAnimation.h"



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

void AG_RaceHUD::SetPlayerPosition(int32 Position)
{
    if (RaceHUDWidget)
    {
        RaceHUDWidget->SetPlayerPosition(Position);
    }
}

void AG_RaceHUD::ShowFinishRaceWidget()
{
    if (RaceWinWidget && RaceWinWidget->IsInViewport() && RaceWinWidget->RaceWinAnimation)
    {
        FTimerHandle AnimationFinishedTimer;
        GetWorld()->GetTimerManager().SetTimer(
            AnimationFinishedTimer, [this]() { ShowFinishRaceWidget(); }, RaceWinWidget->RaceWinAnimation->GetEndTime(), false);
        return;
    }

    RaceFinishWidget = CreateWidget<UG_RaceFinishWidget>(GetOwningPlayerController(), FinishRaceWidgetClass);
    if (RaceFinishWidget)
    {
        RaceFinishWidget->AddToViewport();
        SetHUDWidgetVisibility(ESlateVisibility::Collapsed);
        SetSpectatorHUDWidgetVisibility(ESlateVisibility::Collapsed);
    }
}

void AG_RaceHUD::ShowWinRaceWidget(int32 Place)
{
    RaceWinWidget = CreateWidget<UG_RaceWinWidget>(GetOwningPlayerController(), WinRaceWidgetClass);
    if (RaceWinWidget)
    {
        RaceWinWidget->SetPlace(Place);
        RaceWinWidget->AddToViewport();
        SetHUDWidgetVisibility(ESlateVisibility::Collapsed);
        SetSpectatorHUDWidgetVisibility(ESlateVisibility::Visible);
        bIsSpectator = true;
    }
}
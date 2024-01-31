// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/HUD/G_HUD.h"
#include "UI/Widgets/G_TableStatsWidget.h"
#include "UI/Widgets/G_PauseWidget.h"
#include <UI/Widgets/G_StartGameWidget.h>
#include <Player/G_PlayerController.h>
#include <Kismet/GameplayStatics.h>
#include "UI/Widgets/G_RaceHUDWidget.h"

void AG_HUD::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    if (TableStatsClass)
    {
        TableStatsWidget = CreateWidget<UG_TableStatsWidget>(GetOwningPlayerController(), TableStatsClass);
        if (TableStatsWidget)
        {
            TableStatsWidget->SetVisibility(ESlateVisibility::Collapsed);
            TableStatsWidget->AddToViewport();
        }
    }

    if (PauseWidgetClass)
    {
        PauseWidget = CreateWidget<UG_PauseWidget>(GetOwningPlayerController(), PauseWidgetClass);
        if (PauseWidget)
        {
            PauseWidget->SetVisibility(ESlateVisibility::Collapsed);
            PauseWidget->AddToViewport();
        }
    }
}

void AG_HUD::SetHUDWidgetVisibility(ESlateVisibility InVisibility)
{
    if (HUDWidget)
    {
        HUDWidget->SetVisibility(InVisibility);
    }
}

void AG_HUD::SetSpectatorHUDWidgetVisibility(ESlateVisibility InVisibility)
{
    if (SpectatorHUDWidget)
    {
        SpectatorHUDWidget->SetVisibility(InVisibility);
    }
}

void AG_HUD::ToggleStatsTable(bool bEnable)
{
    if (!TableStatsWidget) return;

    if (bEnable)
    {
        TableStatsWidget->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        TableStatsWidget->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void AG_HUD::Pause(bool bPause)
{
    if (!PauseWidget) return;

    if (bPause)
    {
        PauseWidget->SetKeyboardFocus();
        PauseWidget->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        PauseWidget->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void AG_HUD::ExitToMenu()
{
    /*AAS_PlayerController* OwnerController = Cast<AAS_PlayerController>(GetOwningPlayerController());
    if (!OwnerController) return;

    OwnerController->ExitToMenu();*/
}

void AG_HUD::ShowStartGameWidget(float StartDelayTime)
{
    if (!StartGameWidgetClass) return;
    if (StartGameWidget && StartGameWidget->IsInViewport()) return;

    StartGameWidget = CreateWidget<UG_StartGameWidget>(GetOwningPlayerController(), StartGameWidgetClass);

    if (StartGameWidget)
    {
        StartGameWidget->InitializeWidget(StartDelayTime);
        StartGameWidget->AddToViewport();
    }

    if (HUDWidget)
    {
        HUDWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}

void AG_HUD::UpdateAbilityUI(FGameplayTagContainer AbilityTags)
{
    if (UG_RaceHUDWidget* RaceHUDWidget = Cast<UG_RaceHUDWidget>(HUDWidget))
    {
        RaceHUDWidget->UpdateAbilityUI(AbilityTags);
    }
}

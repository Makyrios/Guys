// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/HUD/G_HUD.h"
#include "UI/Widgets/G_RaceHUDWidget.h"

void AG_HUD::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    RaceHUDWidget = CreateWidget<UG_RaceHUDWidget>(GetOwningPlayerController(), RaceHUDWidgetClass);
    RaceHUDWidget->AddToViewport();

    /*

    TableStatsWidget = AddWidget<UAS_TableStatsWidget>(StatsTableClass);
    if (TableStatsWidget)
    {
        TableStatsWidget->SetVisibility(ESlateVisibility::Collapsed);

        const FString MapName = UGameplayStatics::GetCurrentLevelName(this);
        TableStatsWidget->SetMapName(FText::FromString(MapName));
    }

    DamageWidget = AddWidget<UAS_DamageWidget>(DamageWidgetClass);

    PauseWidget = AddWidget<UAS_PauseWidget>(PauseWidgetClass);
    if (PauseWidget)
    {
        PauseWidget->SetVisibility(ESlateVisibility::Collapsed);
    }*/
}

void AG_HUD::SetHUDWidgetVisibility(ESlateVisibility InVisibility)
{
    /*
    HUDWidget->SetVisibility
    */
}

void AG_HUD::SetTimeRemaining(float RemainingTimeInSeconds) {}

void AG_HUD::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AG_HUD::ShowStatsTable()
{
    /*
    if (!TableStatsWidget) return;
    TableStatsWidget->SetVisibility(ESlateVisibility::Visible);
    */
}

void AG_HUD::HideStatsTable()
{
    /*
    if (!TableStatsWidget) return;
    TableStatsWidget->SetVisibility(ESlateVisibility::Collapsed);
    */
}

void AG_HUD::Pause(bool bPause)
{
    /*if (!PauseWidget) return;

    if (bPause)
    {
        PauseWidget->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        PauseWidget->SetVisibility(ESlateVisibility::Collapsed);

        AAS_PlayerController* OwnerController = Cast<AAS_PlayerController>(GetOwningPlayerController());
        if (!OwnerController) return;

        OwnerController->UnPause();
    }*/
}

void AG_HUD::ExitToMenu()
{
    /*AAS_PlayerController* OwnerController = Cast<AAS_PlayerController>(GetOwningPlayerController());
    if (!OwnerController) return;

    OwnerController->ExitToMenu();*/
}

void AG_HUD::ShowStartGameWidget(float StartDelayTime)
{
    /*UAS_StartGameWidget* StartGameWidget = AddWidget<UAS_StartGameWidget>(StartGameWidgetClass);

    if (HUDWidget)
    {
        HUDWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (StartGameWidget)
    {
        StartGameWidget->InitializeWidget(StartDelayTime);
    }*/
}

void AG_HUD::ShowWonWidget()
{
    /*
    UUserWidget* WonWidget = AddWidget<UUserWidget>(WonWidgetClass);
    */
}

void AG_HUD::ShowLoseWidget()
{
    /*
    UUserWidget* WonWidget = AddWidget<UUserWidget>(LoseWidgetClass);
    */
}

void AG_HUD::UpdateInventoryInfo()
{
    /*if (!HUDWidget) return;

    HUDWidget->UpdateInventoryInfo();*/
}

void AG_HUD::SetupTableWidget()
{
    /*if (!TableStatsWidget) return;

    const int32 NumberOfPlayers = UGameplayStatics::GetNumPlayerStates(this);
    TableStatsWidget->SetPlayerNumber(NumberOfPlayers);*/
}

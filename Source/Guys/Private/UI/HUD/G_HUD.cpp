// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/HUD/G_HUD.h"
#include "UI/Widgets/G_TableStatsWidget.h"
#include "UI/Widgets/G_PauseWidget.h"
#include <UI/Widgets/G_StartGameWidget.h>

void AG_HUD::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    if (TableStatsWidget)
    {
        TableStatsWidget = CreateWidget<UG_TableStatsWidget>(GetOwningPlayerController(), TableStatsClass);
        if (TableStatsWidget)
        {
            TableStatsWidget->SetVisibility(ESlateVisibility::Collapsed);
            TableStatsWidget->AddToViewport();
        }
    }
    
    if (PauseWidget)
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
    if (!StartGameWidgetClass) return;

    UG_StartGameWidget* StartGameWidget = CreateWidget<UG_StartGameWidget>(GetOwningPlayerController(), StartGameWidgetClass);

    if (HUDWidget)
    {
        HUDWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (StartGameWidget)
    {
        StartGameWidget->InitializeWidget(StartDelayTime);
        StartGameWidget->AddToViewport();
    }
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

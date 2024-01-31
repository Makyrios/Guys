// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/HUD/G_LobbyHUD.h"
#include "UI/Widgets/G_LobbyHUDWidget.h"

void AG_LobbyHUD::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    if (LobbyHUDWidgetClass)
    {
        LobbyHUDWidget = CreateWidget<UG_LobbyHUDWidget>(GetOwningPlayerController(), LobbyHUDWidgetClass);
        if (LobbyHUDWidget)
        {
            LobbyHUDWidget->AddToViewport();
            HUDWidget = LobbyHUDWidget;
        }
    }
}

void AG_LobbyHUD::SetTimeRemaining(float RemainingSeconds)
{
    if (LobbyHUDWidget)
    {
        LobbyHUDWidget->SetTimeRemaining(RemainingSeconds);
    }
}

void AG_LobbyHUD::SetPlayersText(int ConnectedPlayers, int DesiredPlayersNum)
{
    if (LobbyHUDWidget)
    {
        LobbyHUDWidget->SetPlayersText(ConnectedPlayers, DesiredPlayersNum);
    }
}

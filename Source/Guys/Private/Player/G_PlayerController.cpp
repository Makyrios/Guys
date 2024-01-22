// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/G_PlayerController.h"
#include <UI/HUD/G_HUD.h>

AG_PlayerController::AG_PlayerController()
{
    bReplicates = true;
}

void AG_PlayerController::CreateStartGameWidget(float DelayBeforeStart)
{
    if (HasAuthority() && IsLocalController())
    {
        ShowStartGameWidget(DelayBeforeStart);
    }
    else
    {
        Client_CreateStartGameWidget(DelayBeforeStart);
    }
}

void AG_PlayerController::ShowStartGameWidget(float DelayBeforeStart)
{
    G_HUD = (!G_HUD) ? GetHUD<AG_HUD>() : G_HUD;
    if (!G_HUD) return;

    G_HUD->ShowStartGameWidget(DelayBeforeStart);
}

void AG_PlayerController::Client_CreateStartGameWidget_Implementation(float DelayBeforeStart)
{
    ShowStartGameWidget(DelayBeforeStart);
}

void AG_PlayerController::SetHUDWidgetVisibility(ESlateVisibility InVisibility)
{
    if (!IsLocalController())
    {
        Client_SetHUDWidgetVisibility(InVisibility);
    }

    G_HUD = (!G_HUD) ? GetHUD<AG_HUD>() : G_HUD;
    if (!G_HUD) return;

    G_HUD->SetHUDWidgetVisibility(InVisibility);
}

void AG_PlayerController::Client_SetHUDWidgetVisibility_Implementation(ESlateVisibility InVisibility)
{
    SetHUDWidgetVisibility(InVisibility);
}

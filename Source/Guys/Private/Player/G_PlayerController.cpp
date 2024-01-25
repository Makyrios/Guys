// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/G_PlayerController.h"
#include <UI/HUD/G_HUD.h>
#include <Character/G_Character.h>
#include <GameFramework/GameMode.h>
#include "Net/UnrealNetwork.h"
#include <Components/SlateWrapperTypes.h>
#include "GameFramework/SpectatorPawn.h"
#include <GameInstance/G_GameInstance.h>
#include <Kismet/GameplayStatics.h>
#include "UI/Widgets/G_PauseWidget.h"

AG_PlayerController::AG_PlayerController()
{
    bReplicates = true;
}

void AG_PlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AG_PlayerController, CurrentMatchState);
}

void AG_PlayerController::TogglePause()
{
    G_HUD = (!G_HUD) ? GetHUD<AG_HUD>() : G_HUD;
    if (!G_HUD) return;

    if (bIsPaused)
    {
        bIsPaused = false;
        G_HUD->Pause(false);
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
        SetHUDWidgetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        SetHUDWidgetVisibility(ESlateVisibility::Collapsed);
        bIsPaused = true;
        G_HUD->Pause(true);
        FInputModeUIOnly InputMode;
        SetInputMode(InputMode);
        bShowMouseCursor = true;
    }
}

void AG_PlayerController::ExitToMenu()
{
    UG_GameInstance* GameInstance = GetGameInstance<UG_GameInstance>();
    if (!GameInstance) return;

    UGameplayStatics::OpenLevel(this, GameInstance->GetMenuMapName());
}

ASpectatorPawn* AG_PlayerController::SpawnSpectatorPawn()
{
    return GetWorld()->SpawnActor<ASpectatorPawn>(GetSpawnLocation(), GetControlRotation());
}

void AG_PlayerController::SetSpectatorHUD(bool bEnableSpectator)
{
    if (bEnableSpectator)
    {
        SetSpectatorHUDWidgetVisibility(ESlateVisibility::Visible);
        SetHUDWidgetVisibility(ESlateVisibility::Collapsed);
    }
    else
    {
        SetSpectatorHUDWidgetVisibility(ESlateVisibility::Collapsed);
        SetHUDWidgetVisibility(ESlateVisibility::Visible);
    }
}

void AG_PlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (!InPawn) return;

    if (CurrentMatchState != MatchState::InProgress)
    {
        SetKeyboardInput(false);
    }
}

void AG_PlayerController::AcknowledgePossession(APawn* InPawn)
{
    Super::AcknowledgePossession(InPawn);

    if (CurrentMatchState != MatchState::InProgress)
    {
        if (GetRemoteRole() == ROLE_Authority)
        {
            Client_SetKeyboardInput(false);
        }
    }
}

void AG_PlayerController::SetKeyboardInput(bool bEnable)
{
    if (HasAuthority() && IsLocalController())
    {
        G_Character = G_Character.IsValid() ? G_Character : Cast<AG_Character>(GetPawn());
        if (!G_Character.IsValid()) return;

        G_Character->SetKeyboardInput(bEnable);
    }
    else
    {
        Client_SetKeyboardInput(bEnable);
    }
}

void AG_PlayerController::Client_SetKeyboardInput_Implementation(bool bEnable)
{
    if (GetPawn())
    {
        G_Character = G_Character.IsValid() ? G_Character : Cast<AG_Character>(GetPawn());
        if (!G_Character.IsValid()) return;

        G_Character->SetKeyboardInput(bEnable);
    }
}

void AG_PlayerController::SetCurrentMatchState(FName InMatchState)
{
    CurrentMatchState = InMatchState;

    if (CurrentMatchState == MatchState::InProgress)
    {
        SetKeyboardInput(true);
    }
    else
    {
        SetKeyboardInput(false);
    }
}

void AG_PlayerController::CreateStartGameWidget(float DelayBeforeStart)
{
    if (HasAuthority() && IsLocalController())
    {
        ShowStartGameWidget(DelayBeforeStart);
    }
    else
    {
        Client_ShowStartGameWidget(DelayBeforeStart);
    }
}

void AG_PlayerController::Client_ShowStartGameWidget_Implementation(float DelayBeforeStart)
{
    ShowStartGameWidget(DelayBeforeStart);
}

void AG_PlayerController::ShowStartGameWidget(float DelayBeforeStart)
{
    G_HUD = (!G_HUD) ? GetHUD<AG_HUD>() : G_HUD;
    if (!G_HUD) return;

    G_HUD->ShowStartGameWidget(DelayBeforeStart);
}

void AG_PlayerController::SetHUDWidgetVisibility(ESlateVisibility InVisibility)
{
    if (bIsPaused || CurrentMatchState != MatchState::InProgress)
    {
    	return;
    }

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

void AG_PlayerController::SetSpectatorHUDWidgetVisibility(ESlateVisibility InVisibility)
{
    if (!IsLocalController())
    {
        Client_SetSpectatorHUDWidgetVisibility(InVisibility);
    }

    G_HUD = (!G_HUD) ? GetHUD<AG_HUD>() : G_HUD;
    if (!G_HUD) return;

    G_HUD->SetSpectatorHUDWidgetVisibility(InVisibility);
}

void AG_PlayerController::Client_SetSpectatorHUDWidgetVisibility_Implementation(ESlateVisibility InVisibility)
{
    SetSpectatorHUDWidgetVisibility(InVisibility);
}

void AG_PlayerController::OnRep_CurrentMatchState()
{
    if (CurrentMatchState == MatchState::WaitingToStart || CurrentMatchState == MatchState::EnteringMap)
    {
        SetKeyboardInput(false);
    }
    else if (CurrentMatchState == MatchState::InProgress)
    {
        SetKeyboardInput(true);
    }
}

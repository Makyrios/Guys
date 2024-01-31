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
#include <GameModes/G_BaseGameMode.h>

AG_PlayerController::AG_PlayerController()
{
    bReplicates = true;

    /* Clamp camera look */
    if (PlayerCameraManager)
    {
        PlayerCameraManager->ViewPitchMin = -45.0f;
        PlayerCameraManager->ViewPitchMax = 10.0f;
    }
}

void AG_PlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AG_PlayerController, CurrentMatchState);
}

void AG_PlayerController::BeginPlay()
{
    Super::BeginPlay();

    BindChangeMatchState();
    ClampCamera();
}

void AG_PlayerController::BindChangeMatchState()
{
    if (HasAuthority())
    {
        if (AG_BaseGameMode* GameMode = Cast<AG_BaseGameMode>(UGameplayStatics::GetGameMode(this)))
        {
            GameMode->OnChangeMatchState.AddUObject(this, &AG_PlayerController::SetCurrentMatchState);
            SetCurrentMatchState(GameMode->GetMatchState());
        }
    }
}

void AG_PlayerController::ClampCamera()
{
    PlayerCameraManager->ViewPitchMax = MaxPitch;
    PlayerCameraManager->ViewPitchMin = MinPitch;
}

void AG_PlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (!InPawn) return;

    if (CurrentMatchState != MatchState::InProgress)
    {
        SetKeyboardInput(false);
    }
    else
    {
        SetKeyboardInput(true);
    }
}

void AG_PlayerController::AcknowledgePossession(APawn* InPawn)
{
    Super::AcknowledgePossession(InPawn);

    if (GetRemoteRole() == ROLE_Authority)
    {
        if (CurrentMatchState != MatchState::InProgress)
        {
            Client_SetKeyboardInput(false);
        }
        else
        {
            Client_SetKeyboardInput(true);
        }
    }
}

void AG_PlayerController::SetKeyboardInput(bool bEnable)
{
    if (!IsLocalController())
    {
        Client_SetKeyboardInput(bEnable);
        return;
    }

    G_Character = G_Character.IsValid() ? G_Character : Cast<AG_Character>(GetPawn());
    if (!G_Character.IsValid()) return;

    G_Character->SetKeyboardInput(bEnable);
}

void AG_PlayerController::Client_SetKeyboardInput_Implementation(bool bEnable)
{
    G_Character = G_Character.IsValid() ? G_Character : Cast<AG_Character>(GetPawn());
    if (!G_Character.IsValid()) return;

    G_Character->SetKeyboardInput(bEnable);
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

void AG_PlayerController::SetHUDWidgetVisibility(ESlateVisibility InVisibility)
{
    if (!ShouldChangeHUDVisibility())
    {
        return;
    }

    if (!GetPawn()) return;
    if (GetPawn()->IsA<ASpectatorPawn>())
    {
        SetSpectatorHUDWidgetVisibility(InVisibility);
    }
    else
    {
        SetPlayerHUDWidgetVisibility(InVisibility);
    }
}

void AG_PlayerController::ToggleStats()
{
    G_HUD = (!G_HUD) ? GetHUD<AG_HUD>() : G_HUD;
    if (!G_HUD) return;

    if (bIsStats)
    {
        bIsStats = false;
        G_HUD->ToggleStatsTable(false);
        SetHUDWidgetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        SetHUDWidgetVisibility(ESlateVisibility::Collapsed);
        bIsStats = true;
        G_HUD->ToggleStatsTable(true);
    }
}

void AG_PlayerController::ExitToMenu()
{
    UG_GameInstance* GameInstance = GetGameInstance<UG_GameInstance>();
    if (!GameInstance) return;

    UGameplayStatics::OpenLevel(this, GameInstance->GetMenuMapName());
}

void AG_PlayerController::UpdateAbilityUI(FGameplayTagContainer AbilityTags)
{
    if (!IsLocalController())
    {
        Client_UpdateAbilityUI(AbilityTags);
        return;
    }

    G_HUD = (!G_HUD) ? GetHUD<AG_HUD>() : G_HUD;
    if (!G_HUD) return;

    G_HUD->UpdateAbilityUI(AbilityTags);
}

void AG_PlayerController::Client_UpdateAbilityUI_Implementation(FGameplayTagContainer AbilityTags)
{
    UpdateAbilityUI(AbilityTags);
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

void AG_PlayerController::SetCurrentMatchState(FName InMatchState)
{
    CurrentMatchState = InMatchState;

    if (CurrentMatchState == MatchState::InProgress)
    {
        SetKeyboardInput(true);
        SetHUDWidgetVisibility(ESlateVisibility::Visible);
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

void AG_PlayerController::ShowStartGameWidget(float DelayBeforeStart)
{
    G_HUD = (!G_HUD) ? GetHUD<AG_HUD>() : G_HUD;
    if (!G_HUD) return;

    G_HUD->ShowStartGameWidget(DelayBeforeStart);
}

void AG_PlayerController::Client_ShowStartGameWidget_Implementation(float DelayBeforeStart)
{
    ShowStartGameWidget(DelayBeforeStart);
}

bool AG_PlayerController::ShouldChangeHUDVisibility()
{
    return !bIsPaused && CurrentMatchState == MatchState::InProgress;
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

void AG_PlayerController::SetPlayerHUDWidgetVisibility(ESlateVisibility InVisibility)
{
    if (!IsLocalController())
    {
        Client_SetPlayerHUDWidgetVisibility(InVisibility);
    }

    G_HUD = (!G_HUD) ? GetHUD<AG_HUD>() : G_HUD;
    if (!G_HUD) return;

    G_HUD->SetHUDWidgetVisibility(InVisibility);
}

void AG_PlayerController::Client_SetPlayerHUDWidgetVisibility_Implementation(ESlateVisibility InVisibility)
{
    SetPlayerHUDWidgetVisibility(InVisibility);
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

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "G_PlayerController.generated.h"

class AG_Character;
class AG_HUD;

UCLASS()
class GUYS_API AG_PlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AG_PlayerController();

    void CreateStartGameWidget(float DelayBeforeStart);
    void SetHUDWidgetVisibility(ESlateVisibility InVisibility);
    bool ShouldChangeHUDVisibility();
    void SetKeyboardInput(bool bEnable);
    void SetSpectatorHUD(bool bEnableSpectator);
    void TogglePause();
    void ToggleStats();
    void ExitToMenu();

    FORCEINLINE FName GetCurrentMatchState() const { return CurrentMatchState; }
    void SetCurrentMatchState(FName InMatchState);

protected:
    virtual void BeginPlay() override;
    void BindChangeMatchState();
    void ClampCamera();
    virtual void OnPossess(APawn* InPawn) override;
    virtual void AcknowledgePossession(APawn* InPawn) override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
    void ShowStartGameWidget(float DelayBeforeStart);
    void SetSpectatorHUDWidgetVisibility(ESlateVisibility InVisibility);
    void SetPlayerHUDWidgetVisibility(ESlateVisibility InVisibility);

    UFUNCTION(Client, Reliable)
    void Client_ShowStartGameWidget(float DelayBeforeStart);

    UFUNCTION(Client, Reliable)
    void Client_SetPlayerHUDWidgetVisibility(ESlateVisibility InVisibility);

    UFUNCTION(Client, Reliable)
    void Client_SetSpectatorHUDWidgetVisibility(ESlateVisibility InVisibility);

    UFUNCTION(Client, Reliable)
    void Client_SetKeyboardInput(bool bEnable);

    UFUNCTION()
    void OnRep_CurrentMatchState();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "G|Camera")
    float MaxPitch = 30.f;

    UPROPERTY(EditDefaultsOnly, Category = "G|Camera")
    float MinPitch = -75.f;

private:
    UPROPERTY()
    TWeakObjectPtr<AG_Character> G_Character;

    UPROPERTY()
    TObjectPtr<AG_HUD> G_HUD;

    UPROPERTY(ReplicatedUsing = OnRep_CurrentMatchState)
    FName CurrentMatchState;

    bool bIsPaused = false;
    bool bIsStats = false;
};

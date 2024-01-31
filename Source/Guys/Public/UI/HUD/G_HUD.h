// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include <GameplayTagContainer.h>
#include "G_HUD.generated.h"

class UG_RaceHUDWidget;
class UG_TableStatsWidget;
class UG_PauseWidget;
class UG_StartGameWidget;

UCLASS()
class GUYS_API AG_HUD : public AHUD
{
    GENERATED_BODY()

public:
    void SetHUDWidgetVisibility(ESlateVisibility InVisibility);
    void SetSpectatorHUDWidgetVisibility(ESlateVisibility InVisibility);

    void ToggleStatsTable(bool bEnable);
    void Pause(bool bPause);
    void ExitToMenu();

    void ShowStartGameWidget(float StartDelayTime);

    void UpdateAbilityUI(FGameplayTagContainer AbilityTags);

protected:
    virtual void PostInitializeComponents() override;

public:
    UPROPERTY()
    TObjectPtr<UUserWidget> HUDWidget;

    UPROPERTY()
    TObjectPtr<UUserWidget> SpectatorHUDWidget;

    UPROPERTY()
    TObjectPtr<UG_PauseWidget> PauseWidget;

    UPROPERTY()
    TObjectPtr<UG_TableStatsWidget> TableStatsWidget;

    UPROPERTY()
    TObjectPtr<UG_StartGameWidget> StartGameWidget;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "AS|Widgets")
    TSubclassOf<UUserWidget> StartGameWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "AS|Widgets")
    TSubclassOf<UUserWidget> TableStatsClass;

    UPROPERTY(EditDefaultsOnly, Category = "AS|Widgets")
    TSubclassOf<UUserWidget> PauseWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "AS|Widgets")
    TSubclassOf<UUserWidget> WonWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "AS|Widgets")
    TSubclassOf<UUserWidget> LoseWidgetClass;
};

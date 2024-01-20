// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "G_HUD.generated.h"

class UG_RaceHUDWidget;
class UG_TableStatsWidget;
class UG_PauseWidget;

UCLASS()
class GUYS_API AG_HUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void PostInitializeComponents() override;

    void SetHUDWidgetVisibility(ESlateVisibility InVisibility);

    void SetTimeRemaining(float RemainingTimeInSeconds);

    void Tick(float DeltaTime) override;

    void ShowStatsTable();
    void HideStatsTable();

    void Pause(bool bPause);
    void ExitToMenu();

    void ShowStartGameWidget(float StartDelayTime);

    void ShowWonWidget();
    void ShowLoseWidget();

    void UpdateInventoryInfo();

protected:
    void SetupTableWidget();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "AS|Widgets")
    TSubclassOf<UUserWidget> RaceHUDWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "AS|Widgets")
    TSubclassOf<UUserWidget> StartGameWidgetClass;

    UPROPERTY()
    TObjectPtr<UG_RaceHUDWidget> RaceHUDWidget;

    UPROPERTY(EditDefaultsOnly, Category = "AS|Widgets")
    TSubclassOf<UUserWidget> StatsTableClass;

    /*UPROPERTY()
    TObjectPtr<UG_TableStatsWidget> TableStatsWidget;*/

    UPROPERTY(EditDefaultsOnly, Category = "AS|Widgets")
    TSubclassOf<UUserWidget> PauseWidgetClass;

    /*UPROPERTY()
    TObjectPtr<UAS_PauseWidget> PauseWidget;*/

    UPROPERTY(EditDefaultsOnly, Category = "AS|Widgets")
    TSubclassOf<UUserWidget> WonWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "AS|Widgets")
    TSubclassOf<UUserWidget> LoseWidgetClass;

};

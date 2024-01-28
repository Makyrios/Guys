// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/G_HUD.h"
#include "G_RaceHUD.generated.h"

class UG_RaceHUDWidget;
class UG_RaceSpectatorHUDWidget;
class UG_RaceWinWidget;
class UG_RaceFinishWidget;

UCLASS()
class GUYS_API AG_RaceHUD : public AG_HUD
{
    GENERATED_BODY()

public:
    void SetTimeRemaining(float RemainingSeconds);

    void SetPlayerPosition(int32 Position);

    void ShowFinishRaceWidget();

    void ShowWinRaceWidget(int32 Place);

protected:
    virtual void PostInitializeComponents() override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "AS|Widgets")
    TSubclassOf<UUserWidget> RaceHUDWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "AS|Widgets")
    TSubclassOf<UUserWidget> RaceSpectatorHUDWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "AS|Widgets")
    TSubclassOf<UUserWidget> FinishRaceWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "AS|Widgets")
    TSubclassOf<UUserWidget> WinRaceWidgetClass;

    UPROPERTY()
    TObjectPtr<UG_RaceHUDWidget> RaceHUDWidget;

    UPROPERTY()
    TObjectPtr<UG_RaceSpectatorHUDWidget> RaceSpectatorHUDWidget;

    TObjectPtr<UG_RaceWinWidget> RaceWinWidget;
    TObjectPtr<UG_RaceFinishWidget> RaceFinishWidget;

    bool bIsSpectator = false;
};

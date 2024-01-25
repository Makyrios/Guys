// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/G_HUD.h"
#include "G_RaceHUD.generated.h"

class UG_RaceHUDWidget;
class UG_RaceSpectatorHUDWidget;

UCLASS()
class GUYS_API AG_RaceHUD : public AG_HUD
{
    GENERATED_BODY()

public:
    void SetTimeRemaining(float RemainingSeconds);

    void ShowFinishRaceWidget();

    void ShowWinRaceWidget();

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

    bool bIsSpectator = false;
};

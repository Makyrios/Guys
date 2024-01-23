// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/G_HUD.h"
#include "G_RaceHUD.generated.h"

UCLASS()
class GUYS_API AG_RaceHUD : public AG_HUD
{
    GENERATED_BODY()

public:
    void SetTimeRemaining(float RemainingSeconds);

    void ShowTimer();

    void ShowFinishRaceWidget();

    void ShowWinRaceWidget();

protected:
    virtual void PostInitializeComponents() override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "AS|Widgets")
    TSubclassOf<UUserWidget> RaceHUDWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "AS|Widgets")
    TSubclassOf<UUserWidget> FinishRaceWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "AS|Widgets")
    TSubclassOf<UUserWidget> WinRaceWidgetClass;

    UPROPERTY()
    TObjectPtr<UG_RaceHUDWidget> RaceHUDWidget;

};

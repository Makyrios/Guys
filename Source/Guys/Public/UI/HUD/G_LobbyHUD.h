// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/G_HUD.h"
#include "G_LobbyHUD.generated.h"

class UG_LobbyHUDWidget;

UCLASS()
class GUYS_API AG_LobbyHUD : public AG_HUD
{
    GENERATED_BODY()

public:
    void SetTimeRemaining(float RemainingSeconds);

protected:
    virtual void PostInitializeComponents() override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "AS|Widgets")
    TSubclassOf<UUserWidget> LobbyHUDWidgetClass;

    UPROPERTY()
    TObjectPtr<UG_LobbyHUDWidget> LobbyHUDWidget;
};

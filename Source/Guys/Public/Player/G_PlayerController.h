// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "G_PlayerController.generated.h"

class AG_HUD;

UCLASS()
class GUYS_API AG_PlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AG_PlayerController();

    void CreateStartGameWidget(float DelayBeforeStart);

    void SetHUDWidgetVisibility(ESlateVisibility InVisibility);

private:
    void ShowStartGameWidget(float DelayBeforeStart);

    UFUNCTION(Client, Reliable)
    void Client_CreateStartGameWidget(float DelayBeforeStart);

    UFUNCTION(Client, Reliable)
    void Client_SetHUDWidgetVisibility(ESlateVisibility InVisibility);

private:
    AG_HUD* G_HUD;
};

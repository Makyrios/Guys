// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "G_RaceSpectatorHUDWidget.generated.h"

class UG_TimerWidget;

UCLASS()
class GUYS_API UG_RaceSpectatorHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetTimeText(float RemainingSeconds);

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UG_TimerWidget> Timer;
};

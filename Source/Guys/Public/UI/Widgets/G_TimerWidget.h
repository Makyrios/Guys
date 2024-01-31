// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "G_TimerWidget.generated.h"

class UTextBlock;
class USizeBox;

UCLASS()
class GUYS_API UG_TimerWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetTimerText(float RemainingSeconds);

private:
    void ShowTimer();

private:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<USizeBox> TimerSizeBox;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> TimerText;
};

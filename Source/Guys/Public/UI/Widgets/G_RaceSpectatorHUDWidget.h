// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "G_RaceSpectatorHUDWidget.generated.h"

class UTextBlock;

UCLASS()
class GUYS_API UG_RaceSpectatorHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetTimeText(float RemainingSeconds);

protected:
    void NativePreConstruct() override;

private:
    void ShowTimer();

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UTextBlock> TimeText;
};

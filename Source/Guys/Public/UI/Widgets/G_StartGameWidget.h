// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "G_StartGameWidget.generated.h"

class UCanvasPanel;
class UTextBlock;

UCLASS()
class GUYS_API UG_StartGameWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void InitializeWidget(float DelayStartTimer);

private:
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UCanvasPanel> Canvas;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UTextBlock> DisplayText;

private:
    float StartGameDelay;
    float Timer;

    bool bStartTimer = false;
};

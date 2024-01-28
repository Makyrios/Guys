// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "G_RaceWinWidget.generated.h"

class UTextBlock;

UCLASS()
class GUYS_API UG_RaceWinWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetPlace(int32 Place);

protected:
    virtual void NativeConstruct() override;

    void BindAnimationFinished();

private:
    UFUNCTION()
    void OnAnimationFinish();

public:
    UPROPERTY(Transient, BlueprintReadWrite, meta = (BindWidgetAnim))
    UWidgetAnimation* RaceWinAnimation;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* PlaceText;
};

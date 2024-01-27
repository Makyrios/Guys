// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "G_RaceFinishWidget.generated.h"


UCLASS()
class GUYS_API UG_RaceFinishWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

    void BindAnimationFinished();

private:
    UFUNCTION()
    void OnAnimationFinish();

public:
    UPROPERTY(Transient, BlueprintReadWrite, meta = (BindWidgetAnim))
    UWidgetAnimation* RaceFinishAnimation;
};

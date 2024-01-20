// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "G_PauseWidget.generated.h"

class UButton;
class AG_HUD;
class USlider;
class UG_GameInstance;

UCLASS()
class GUYS_API UG_PauseWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

private:
    UFUNCTION()
    void OnPlayButtonClicked();

    UFUNCTION()
    void OnExitButtonClicked();

    UFUNCTION()
    void OnVolumeSliderValueChanged(float Value);

public:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> PlayButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> ExitButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<USlider> VolumeSlider;

private:
    /*UPROPERTY()
    UG_GameInstance* G_GameInstance;*/

    UPROPERTY()
    AG_HUD* G_HUD;
};

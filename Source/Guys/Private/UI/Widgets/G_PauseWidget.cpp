// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/G_PauseWidget.h"
#include "UI/HUD/G_HUD.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include <Player/G_PlayerController.h>
#include "GameInstance/G_GameInstance.h"

void UG_PauseWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (!PlayButton || !ExitButton || !VolumeSlider) return;

    PlayButton->OnClicked.AddDynamic(this, &UG_PauseWidget::OnPlayButtonClicked);
    ExitButton->OnClicked.AddDynamic(this, &UG_PauseWidget::OnExitButtonClicked);

    VolumeSlider->OnValueChanged.AddDynamic(this, &UG_PauseWidget::OnVolumeSliderValueChanged);

    G_GameInstance = G_GameInstance.IsValid() ? G_GameInstance : GetGameInstance<UG_GameInstance>();
    if (!G_GameInstance.IsValid()) return;

    VolumeSlider->SetValue(G_GameInstance->GetMasterSoundVolume());
}

FReply UG_PauseWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    if (InKeyEvent.GetKey() == EKeys::Escape || InKeyEvent.GetKey() == EKeys::P)
    {
        OnPlayButtonClicked();
        return FReply::Handled();
    }
    return FReply::Unhandled();
}

void UG_PauseWidget::OnPlayButtonClicked()
{
    if (!GetOwningPlayer()) return;

    PlayerController = PlayerController.IsValid() ? PlayerController : GetOwningPlayer<AG_PlayerController>();
    if (!PlayerController.IsValid()) return;

    PlayerController->TogglePause();
}

void UG_PauseWidget::OnExitButtonClicked()
{
    if (!GetOwningPlayer()) return;

    PlayerController = PlayerController.IsValid() ? PlayerController : GetOwningPlayer<AG_PlayerController>();
    if (!PlayerController.IsValid()) return;

    PlayerController->ExitToMenu();
}

void UG_PauseWidget::OnVolumeSliderValueChanged(float Value)
{
    G_GameInstance = G_GameInstance.IsValid() ? G_GameInstance : GetGameInstance<UG_GameInstance>();
    if (!G_GameInstance.IsValid()) return;

    G_GameInstance->SetMasterSoundVolume(Value);
}

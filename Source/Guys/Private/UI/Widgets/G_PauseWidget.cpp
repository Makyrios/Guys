// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/G_PauseWidget.h"
#include "UI/HUD/G_HUD.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include <Player/G_PlayerController.h>

void UG_PauseWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (!PlayButton || !ExitButton || !VolumeSlider) return;

    PlayButton->OnClicked.AddDynamic(this, &UG_PauseWidget::OnPlayButtonClicked);
    ExitButton->OnClicked.AddDynamic(this, &UG_PauseWidget::OnExitButtonClicked);

    VolumeSlider->OnValueChanged.AddDynamic(this, &UG_PauseWidget::OnVolumeSliderValueChanged);

    /*
    AG_GameInstance = (!AG_GameInstance) ? GetGameInstance<UG_GameInstance>() : AG_GameInstance;
    if (!AG_GameInstance) return;

    VolumeSlider->SetValue(AG_GameInstance->GetMasterSoundVolume());
    */

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
    /*
    AG_GameInstance = (!AG_GameInstance) ? GetGameInstance<UAG_GameInstance>() : AG_GameInstance;
    if (!AG_GameInstance) return;

    AG_GameInstance->SetMasterSoundVolume(Value);
    */
}

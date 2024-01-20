// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/G_PauseWidget.h"
#include "UI/HUD/G_HUD.h"
#include "Components/Button.h"
#include "Components/Slider.h"

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

void UG_PauseWidget::OnPlayButtonClicked()
{
    if (!GetOwningPlayer() || !GetOwningPlayer()->GetHUD()) return;

    G_HUD = (!G_HUD) ? Cast<AG_HUD>(GetOwningPlayer()->GetHUD()) : G_HUD;
    if (!G_HUD) return;

    G_HUD->Pause(false);
}

void UG_PauseWidget::OnExitButtonClicked()
{
    if (!GetOwningPlayer() || !GetOwningPlayer()->GetHUD()) return;

    G_HUD = (!G_HUD) ? Cast<AG_HUD>(GetOwningPlayer()->GetHUD()) : G_HUD;
    if (!G_HUD) return;

    G_HUD->ExitToMenu();
}

void UG_PauseWidget::OnVolumeSliderValueChanged(float Value) 
{
    /*
    AG_GameInstance = (!AG_GameInstance) ? GetGameInstance<UAG_GameInstance>() : AG_GameInstance;
    if (!AG_GameInstance) return;

    AG_GameInstance->SetMasterSoundVolume(Value);
    */
}

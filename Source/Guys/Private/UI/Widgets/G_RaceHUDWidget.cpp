// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/G_RaceHUDWidget.h"
#include "UI/Widgets/G_InventoryWidget.h"
#include <Components/TextBlock.h>
#include <Kismet/KismetStringLibrary.h>
#include "Components/Image.h"
#include <GameModes/G_RaceGameMode.h>
#include <Kismet/GameplayStatics.h>

void UG_RaceHUDWidget::SetTimeText(float RemainingSeconds)
{
    if (!TimeText) return;

    if (TimeText->GetVisibility() != ESlateVisibility::Visible)
    {
        ShowTimer();
    }

    if (RemainingSeconds >= 0)
    {
        FString TimerString = UKismetStringLibrary::TimeSecondsToString(RemainingSeconds);
        TimerString.RemoveAt(5, 3);
        TimeText->SetText(FText::FromString(TimerString));
    }
}

void UG_RaceHUDWidget::ShowTimer()
{
    if (TimeText)
    {
        TimeText->SetVisibility(ESlateVisibility::Visible);
    }
}

void UG_RaceHUDWidget::SetFirstAbilityImage(FGameplayTag AbilityTag)
{
    /*UImage* AbilityImage = GetAbilityImage(AbilityTag);
    if (AbilityImage)
    {
        InventoryWidget->FirstAbilityImage->SetBrushFromTexture(AbilityImage->Brush.GetResourceObject());
    }*/
}

void UG_RaceHUDWidget::SetSecondAbilityImage(FGameplayTag AbilityTag)
{
    /*UImage* AbilityImage = GetAbilityImage(AbilityTag);
    if (AbilityImage)
    {
        InventoryWidget->SecondAbilityImage->SetBrushFromTexture(AbilityImage->Brush.GetResourceObject());
    }*/
}

UImage* UG_RaceHUDWidget::GetAbilityImage(FGameplayTag AbilityTag)
{
    /* TODO - Get ability image from ability tag
    switch (AbilityTag)
    {
    */
    return nullptr;
}

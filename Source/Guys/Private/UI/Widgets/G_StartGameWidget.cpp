// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/G_StartGameWidget.h"
#include "Components/TextBlock.h"
#include "Animation/WidgetAnimation.h"


void UG_StartGameWidget::InitializeWidget(float DelayStartTimer)
{
    StartGameDelay = DelayStartTimer;
    Timer = StartGameDelay;
    bStartTimer = true;
}

void UG_StartGameWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (bStartTimer)
    {
        Timer -= InDeltaTime;
        if (StartGameDelay - Timer < 1)
        {
            DisplayText->SetText(FText::AsNumber(FMath::FloorToInt(Timer)));
            if (!IsAnimationPlaying(TextShrinkAnimation))
            {
                PlayAnimation(TextShrinkAnimation);
            }
        }
        else if (FMath::FloorToInt(Timer) == 0)
        {
            DisplayText->SetText(FText::FromString("Go!"));
            if (!IsAnimationPlaying(TextShrinkAnimation))
            {
                PlayAnimation(TextShrinkAnimation);
            }
        }
        else if (Timer > 0)
        {
            DisplayText->SetText(FText::AsNumber(FMath::FloorToInt(Timer)));
        }
        else
        {
            RemoveFromParent();
        }
    }
}

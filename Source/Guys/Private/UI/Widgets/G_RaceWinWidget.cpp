// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/G_RaceWinWidget.h"
#include "Animation/WidgetAnimation.h"
#include "Components/TextBlock.h"

void UG_RaceWinWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (!RaceWinAnimation) return;

    PlayAnimation(RaceWinAnimation);

    BindAnimationFinished();
}

void UG_RaceWinWidget::BindAnimationFinished()
{
    float AnimationEndTime = RaceWinAnimation->GetEndTime();
    FTimerHandle AnimationFinishedTimer;
    GetWorld()->GetTimerManager().SetTimer(AnimationFinishedTimer, this, &UG_RaceWinWidget::OnAnimationFinish, AnimationEndTime, false);
}

void UG_RaceWinWidget::OnAnimationFinish()
{
    RemoveFromParent();
}

void UG_RaceWinWidget::SetPlace(int32 Place)
{
    if (PlaceText)
    {
        PlaceText->SetText(FText::FromString(FString::FromInt(Place) + " PLACE"));
    }
}

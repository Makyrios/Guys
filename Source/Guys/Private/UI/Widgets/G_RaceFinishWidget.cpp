// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/G_RaceFinishWidget.h"
#include "Animation/WidgetAnimation.h"

void UG_RaceFinishWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (!RaceFinishAnimation) return;

    PlayAnimation(RaceFinishAnimation);

    BindAnimationFinished();
}

void UG_RaceFinishWidget::BindAnimationFinished()
{
    float AnimationEndTime = RaceFinishAnimation->GetEndTime();
    FTimerHandle AnimationFinishedTimer;
    GetWorld()->GetTimerManager().SetTimer(AnimationFinishedTimer, this, &UG_RaceFinishWidget::OnAnimationFinish, AnimationEndTime, false);
}

void UG_RaceFinishWidget::OnAnimationFinish()
{
    RemoveFromParent();
}

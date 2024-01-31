// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/G_RaceHUDWidget.h"
#include "UI/Widgets/G_InventoryWidget.h"
#include <Components/TextBlock.h>
#include <Kismet/KismetStringLibrary.h>
#include <GameModes/G_RaceGameMode.h>
#include <Kismet/GameplayStatics.h>
#include <Actors/G_RaceTrajectorySpline.h>
#include "UI/Widgets/G_TimerWidget.h"

void UG_RaceHUDWidget::SetTimeText(float RemainingSeconds)
{
    if (Timer)
    {
        Timer->SetTimerText(RemainingSeconds);
    }
}

void UG_RaceHUDWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    SetVisibility(ESlateVisibility::Collapsed);
}

void UG_RaceHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();

    TrajectorySpline = Cast<AG_RaceTrajectorySpline>(UGameplayStatics::GetActorOfClass(GetWorld(), AG_RaceTrajectorySpline::StaticClass()));
}

void UG_RaceHUDWidget::SetPlayerPosition(int32 Position)
{
    check(PlaceText);

    if (PlayerPosition == Position) return;

    PlayerPosition = Position;
    FText PosText = FText::AsNumber(Position);
    PlaceText->SetText(PosText);
}

void UG_RaceHUDWidget::UpdateAbilityUI(FGameplayTagContainer AbilityTag)
{
    if (!InventoryWidget) return;

    InventoryWidget->UpdateAbilityUI(AbilityTag);
}

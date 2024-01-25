// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/G_TableStatsWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Components/VerticalBox.h"
#include "Player/G_PlayerState.h"
#include "GameFramework/GameState.h"
#include "UI/Widgets/G_PlayerStatsWidget.h"

void UG_TableStatsWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    GetWorld()->GetTimerManager().SetTimer(UpdateTimer, this, &UG_TableStatsWidget::UpdatePlayers, UpdateDelay, true, 0.0f);
}

void UG_TableStatsWidget::UpdatePlayers()
{
    const AGameStateBase* GameState = UGameplayStatics::GetGameState(this);
    if (!GameState) return;
    const TArray<APlayerState*> PlayerStates = GameState->PlayerArray;

    for (int i = 0; i < PlayerStates.Num(); ++i)
    {
        if (AG_PlayerState* PlayerState = Cast<AG_PlayerState>(PlayerStates[i]))
        {
            if (PlayerStatesInTable.Find(PlayerState) == INDEX_NONE)
            {
                AddPlayerStatsToTable(PlayerState);
            }
        }
    }
}

void UG_TableStatsWidget::AddPlayerStatsToTable(AG_PlayerState* PlayerToAdd)
{
    if (!PlayerToAdd || !PlayerStatsClass) return;

    UG_PlayerStatsWidget* NewPlayerStats = CreateWidget<UG_PlayerStatsWidget>(this, PlayerStatsClass);
    if (!NewPlayerStats || !Players) return;

    PlayerStatesInTable.Add(PlayerToAdd);
    NewPlayerStats->SetPlayerState(PlayerToAdd);
    Players->AddChild(NewPlayerStats);
}

void UG_TableStatsWidget::SetPlayerNumber(int32 PlayerNumber)
{
    if (PlayersNumberBox)
    {
        const FString PlayerNumberString = FString::FromInt(PlayerNumber);
        PlayersNumberBox->SetText(FText::FromString(PlayerNumberString));
    }
}


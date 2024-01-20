// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "G_TableStatsWidget.generated.h"

class UTextBlock;
class UVerticalBox;
class AG_PlayerState;

UCLASS()
class GUYS_API UG_TableStatsWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetPlayerNumber(int32 PlayerNumber);

protected:
    void NativeOnInitialized() override;
    void UpdatePlayers();
    virtual void AddPlayerStatsToTable(AG_PlayerState* PlayerToAdd);

protected:
    UPROPERTY()
    TArray<AG_PlayerState*> PlayerStatesInTable;

    UPROPERTY(EditAnywhere)
    TSubclassOf<UUserWidget> PlayerStatsClass;

    UPROPERTY(EditAnywhere, meta = (BindWidget))
    UTextBlock* PlayersNumberBox;

    UPROPERTY(EditAnywhere, meta = (BindWidget))
    UVerticalBox* Players;

    FTimerHandle UpdateTimer;
    float UpdateDelay = 2.0f;
};

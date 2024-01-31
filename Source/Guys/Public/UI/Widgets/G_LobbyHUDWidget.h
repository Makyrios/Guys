// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "G_LobbyHUDWidget.generated.h"

class UG_TimerWidget;
class UVerticalBox;
class UTextBlock;

UCLASS()
class GUYS_API UG_LobbyHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetTimeRemaining(float RemainingSeconds);

    void SetPlayersText(int ConnectedPlayers, int DesiredPlayersNum);

private:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UVerticalBox> VerticalBox; 

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UG_TimerWidget> Timer;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> PlayersText;
};

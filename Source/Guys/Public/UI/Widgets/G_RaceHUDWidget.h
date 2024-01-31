// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <GameplayTagContainer.h>
#include "G_RaceHUDWidget.generated.h"

class UG_InventoryWidget;
class UTextBlock;
class UImage;
class AG_RaceTrajectorySpline;
class UG_TimerWidget;
class UDataTable;

UCLASS()
class GUYS_API UG_RaceHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetTimeText(float RemainingSeconds);

    FORCEINLINE int32 GetPlayerPosition() const { return PlayerPosition; }
    void SetPlayerPosition(int32 Position);

    void UpdateAbilityUI(FGameplayTagContainer AbilityTags);

protected:
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UG_InventoryWidget> InventoryWidget;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UTextBlock> PlaceText;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UG_TimerWidget> Timer;

private:
    UPROPERTY()
    TWeakObjectPtr<AG_RaceTrajectorySpline> TrajectorySpline;

    int32 PlayerPosition = 0;
};

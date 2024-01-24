// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <GameplayTagContainer.h>
#include "G_RaceHUDWidget.generated.h"

class UG_InventoryWidget;
class UTextBlock;
class UImage;

UCLASS()
class GUYS_API UG_RaceHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetTimeText(float RemainingSeconds);
    void ShowTimer();

    void SetFirstAbilityImage(FGameplayTag AbilityTag);
    void SetSecondAbilityImage(FGameplayTag AbilityTag);

protected:
    void NativePreConstruct() override;

private:
    UImage* GetAbilityImage(FGameplayTag AbilityTag);

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UG_InventoryWidget> InventoryWidget;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UTextBlock> PlaceText;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UTextBlock> TimeText;
};

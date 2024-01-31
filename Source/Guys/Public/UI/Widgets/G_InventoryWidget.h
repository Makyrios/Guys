// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <GameplayTagContainer.h>
#include "G_InventoryWidget.generated.h"

class UCanvasPanel;
class UImage;
class UBorder;
class UDataTable;

UCLASS()
class GUYS_API UG_InventoryWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void UpdateAbilityUI(FGameplayTagContainer AbilityTag);

private:
    void SetFirstAbilityImage(FGameplayTag AbilityTag);
    void SetSecondAbilityImage(FGameplayTag AbilityTag);

    UTexture2D* GetAbilityImage(FGameplayTag AbilityTag);

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UCanvasPanel> Canvas;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UBorder> FirstAbilityBorder;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UImage> FirstAbilityImage;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UBorder> SecondAbilityBorder;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UImage> SecondAbilityImage;

private:
    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UDataTable> AbilityImagesDataTable;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "G_InventoryWidget.generated.h"

class UCanvasPanel;
class UImage;
class UBorder;

UCLASS()
class GUYS_API UG_InventoryWidget : public UUserWidget
{
    GENERATED_BODY()

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
};

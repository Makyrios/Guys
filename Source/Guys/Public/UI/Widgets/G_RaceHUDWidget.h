// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "G_RaceHUDWidget.generated.h"

class UG_InventoryWidget;
class UTextBlock;

UCLASS()
class GUYS_API UG_RaceHUDWidget : public UUserWidget
{
	GENERATED_BODY()

	public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UG_InventoryWidget> InventoryWidget;
	
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UTextBlock> PlaceText;
};

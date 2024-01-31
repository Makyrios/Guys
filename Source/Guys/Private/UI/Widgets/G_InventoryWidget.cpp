// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/G_InventoryWidget.h"
#include <Engine/DataTable.h>
#include "Engine/Texture2D.h"
#include "Misc/G_AbilityImage.h"
#include "Components/Image.h"

void UG_InventoryWidget::UpdateAbilityUI(FGameplayTagContainer AbilityTags)
{
    if (AbilityTags.Num() == 2)
    {
        SetFirstAbilityImage(AbilityTags.GetByIndex(0));
        SetSecondAbilityImage(AbilityTags.GetByIndex(1));
    }
    else if (AbilityTags.Num() == 1)
    {
        SetFirstAbilityImage(AbilityTags.GetByIndex(0));
        SecondAbilityImage->SetVisibility(ESlateVisibility::Hidden);
    }
    else if (AbilityTags.Num() == 0)
    {
        FirstAbilityImage->SetVisibility(ESlateVisibility::Hidden);
		SecondAbilityImage->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UG_InventoryWidget::SetFirstAbilityImage(FGameplayTag AbilityTag)
{
    UTexture2D* AbilityImage = GetAbilityImage(AbilityTag);
    if (AbilityImage)
    {
        FirstAbilityImage->SetBrushFromTexture(AbilityImage);
        FirstAbilityImage->SetVisibility(ESlateVisibility::Visible);
    }
}

void UG_InventoryWidget::SetSecondAbilityImage(FGameplayTag AbilityTag)
{
    UTexture2D* AbilityImage = GetAbilityImage(AbilityTag);
    if (AbilityImage)
    {
        SecondAbilityImage->SetBrushFromTexture(AbilityImage);
        SecondAbilityImage->SetVisibility(ESlateVisibility::Visible);
    }
}

UTexture2D* UG_InventoryWidget::GetAbilityImage(FGameplayTag AbilityTag)
{
    if (!AbilityImagesDataTable) return nullptr;

    const FString ContextString = TEXT("Image");
    FG_AbilityImage* AbilityImageStruct = AbilityImagesDataTable->FindRow<FG_AbilityImage>(AbilityTag.GetTagName(), ContextString, true);
    return AbilityImageStruct->AbilityImage;
}

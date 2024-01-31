// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/G_InventoryWidget.h"
#include <Engine/DataTable.h>
#include "Engine/Texture2D.h"
#include "Misc/G_AbilityImage.h"
#include <GameplayTagContainer.h>
#include "Components/Image.h"

void UG_InventoryWidget::UpdateAbilityUI(FGameplayTagContainer AbilityTags)
{
    if (AbilityTags.Num() == 0) return;

    if (AbilityTags.Num() == 1)
    {
        SetFirstAbilityImage(AbilityTags.GetByIndex(0));
    }
    else if (AbilityTags.Num() == 2)
    {
        SetFirstAbilityImage(AbilityTags.GetByIndex(0));
        SetSecondAbilityImage(AbilityTags.GetByIndex(1));
    }
}

void UG_InventoryWidget::SetFirstAbilityImage(FGameplayTag AbilityTag)
{
    UTexture2D* AbilityImage = GetAbilityImage(AbilityTag);
    if (AbilityImage)
    {
        FirstAbilityImage->SetBrushFromTexture(AbilityImage);
    }
}

void UG_InventoryWidget::SetSecondAbilityImage(FGameplayTag AbilityTag)
{
    UTexture2D* AbilityImage = GetAbilityImage(AbilityTag);
    if (AbilityImage)
    {
        SecondAbilityImage->SetBrushFromTexture(AbilityImage);
    }
}

UTexture2D* UG_InventoryWidget::GetAbilityImage(FGameplayTag AbilityTag)
{
    if (!AbilityImagesDataTable) return nullptr;

    const FString ContextString = TEXT("Image");
    FG_AbilityImage* AbilityImageStruct = AbilityImagesDataTable->FindRow<FG_AbilityImage>(AbilityTag.GetTagName(), ContextString, true);
    return AbilityImageStruct->AbilityImage;

    /*if (AbilityTag == FGameplayTag::RequestGameplayTag(FName("Ability.Untargeted.SpeedUp")))
    {
        const FString ContextString = TEXT("Speed Up Image");
        FG_AbilityImage* AbilityImageStruct = AbilityImagesDataTable->FindRow<FG_AbilityImage>(FName("SpeedUp"), ContextString, true);
        return AbilityImageStruct->AbilityImage;
    }*/

    return nullptr;
}

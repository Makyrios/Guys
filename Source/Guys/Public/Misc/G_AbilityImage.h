// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "G_AbilityImage.generated.h"

USTRUCT(BlueprintType)
struct FG_AbilityImage : public FTableRowBase
{
    GENERATED_BODY()

public:
    FG_AbilityImage();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* AbilityImage;
};

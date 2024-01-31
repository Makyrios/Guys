// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "G_ChosenSkinsIdx.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FG_ChosenSkinsIdx
{
public:
	GENERATED_BODY()
	
    UPROPERTY()
	int32 SkinIdx;

	UPROPERTY()
	int32 HatIdx;

	FG_ChosenSkinsIdx()
	{
		SkinIdx = 0;
		HatIdx = 0;
	}
};

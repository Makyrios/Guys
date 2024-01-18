// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "G_PlayerStart.generated.h"

UCLASS()
class GUYS_API AG_PlayerStart : public APlayerStart
{
	GENERATED_BODY()

public:
    void SetIsOccupied(bool IsOccupied);

    FORCEINLINE bool GetIsOccupied() { return bIsOccupied; }

private:
    UPROPERTY(EditAnywhere, Category = "G|Spawn")
    float OccupiedTime;

    UPROPERTY()
    FTimerHandle OccupiedTimer;

    bool bIsOccupied;
};

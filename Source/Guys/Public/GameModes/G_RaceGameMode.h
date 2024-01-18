// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/G_BaseGameMode.h"
#include "G_RaceGameMode.generated.h"

/**
 *
 */
UCLASS()
class GUYS_API AG_RaceGameMode : public AG_BaseGameMode
{
    GENERATED_BODY()

protected:
    virtual bool ReadyToEndMatch_Implementation() override;
    virtual void HandleMatchHasEnded() override;
};

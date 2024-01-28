// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/G_RacePlayerState.h"
#include "Net/UnrealNetwork.h"


void AG_RacePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AG_RacePlayerState, PlayerScore);
}

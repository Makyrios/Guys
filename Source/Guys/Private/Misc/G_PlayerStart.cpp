// Fill out your copyright notice in the Description page of Project Settings.


#include "Misc/G_PlayerStart.h"

void AG_PlayerStart::SetIsOccupied(bool IsOccupied)
{
    if (IsOccupied)
    {
        GetWorldTimerManager().SetTimer(OccupiedTimer, FTimerDelegate::CreateLambda([&] { bIsOccupied = false; }), OccupiedTime, false);
    }
    bIsOccupied = IsOccupied;
}
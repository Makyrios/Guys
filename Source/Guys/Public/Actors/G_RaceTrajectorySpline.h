// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "G_RaceTrajectorySpline.generated.h"

class USplineComponent;
class AG_RaceGameState;

UCLASS()
class GUYS_API AG_RaceTrajectorySpline : public AActor
{
    GENERATED_BODY()

public:
    AG_RaceTrajectorySpline();

    float GetPlayerProgress(AActor* Player);

protected:
    virtual void BeginPlay() override;

    void BuildIntervalSplinePoints();

    virtual void Tick(float DeltaTime) override;

private:
    void UpdateActorsInWorld();
    TMap<AActor*, float> GetUpdatedPlayerProgressess();
    bool PlayersChangedPositions(); 
    void UpdatePlayerPositions();

private:
    UPROPERTY(VisibleAnywhere, Category = "G|Components")
    TObjectPtr<USplineComponent> SplineComponent;

    UPROPERTY(VisibleAnywhere, Category = "G|Components")
    TObjectPtr<USplineComponent> IntervalSpline;

    UPROPERTY()
    TWeakObjectPtr<AG_RaceGameState> RaceGameState;

    UPROPERTY()
    TArray<AActor*> ActorsInWorld;

    UPROPERTY()
    TMap<AActor*, float> CurrentPlayerProgressesMap;
    UPROPERTY()
    TMap<AActor*, float> PlayerProgressesMap;


};

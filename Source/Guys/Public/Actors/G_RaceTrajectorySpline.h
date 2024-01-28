// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "G_RaceTrajectorySpline.generated.h"

class USplineComponent;

UCLASS()
class GUYS_API AG_RaceTrajectorySpline : public AActor
{
    GENERATED_BODY()

public:
    AG_RaceTrajectorySpline();

    float GetPlayerProgress(AActor* Player);

protected:
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    virtual void OnConstruction(const FTransform& Transform) override;

private:
    void UpdateActorsInWorld();
    TMap<AActor*, float> GetUpdatedPlayerProgressess();
    bool PlayersChangedPositions(TMap<AActor*, float>& CurrentPlayerProgressesMap); 
    void UpdatePlayerPositions();

private:
    UPROPERTY(VisibleAnywhere, Category = "G|Components")
    TObjectPtr<USplineComponent> SplineComponent;

    UPROPERTY(VisibleAnywhere, Category = "G|Components")
    TObjectPtr<USplineComponent> IntervalSpline;

    UPROPERTY()
    TArray<AActor*> ActorsInWorld;

    TMap<AActor*, float> PlayerProgressesMap;
};

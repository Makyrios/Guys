// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/G_RaceTrajectorySpline.h"
#include <Components/SplineComponent.h>
#include <Kismet/GameplayStatics.h>
#include "Character/G_Character.h"
#include "GameFramework/GameStateBase.h"
#include "Player/G_RacePlayerController.h"
#include <Player/G_RacePlayerState.h>


AG_RaceTrajectorySpline::AG_RaceTrajectorySpline()
{
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Component"));
    IntervalSpline = CreateDefaultSubobject<USplineComponent>(TEXT("Interval Spline Component"));
}

void AG_RaceTrajectorySpline::BeginPlay()
{
    Super::BeginPlay();

    check(SplineComponent);
    check(IntervalSpline);

    IntervalSpline->ClearSplinePoints();

    float SplineLength = SplineComponent->GetSplineLength();
    int NumberOfPoints = FMath::TruncToInt(SplineLength / 100);
    for (int i = 0; i < NumberOfPoints; i++)
    {
        FVector PointLocation = SplineComponent->GetLocationAtDistanceAlongSpline(i * 100, ESplineCoordinateSpace::World);
        IntervalSpline->AddSplinePointAtIndex(PointLocation, i, ESplineCoordinateSpace::World);
    }
}

float AG_RaceTrajectorySpline::GetPlayerProgress(AActor* Player)
{
    if (!Player) return -1;

    float PlayerDistance = IntervalSpline->FindInputKeyClosestToWorldLocation(Player->GetActorLocation());
    return PlayerDistance / IntervalSpline->GetNumberOfSplinePoints();
}

void AG_RaceTrajectorySpline::OnConstruction(const FTransform& Transform) 
{
    Super::OnConstruction(Transform);
    
}

void AG_RaceTrajectorySpline::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UpdateActorsInWorld();

    TMap<AActor*, float> CurrentPlayerProgressesMap = GetUpdatedPlayerProgressess();
    CurrentPlayerProgressesMap.ValueSort([](const float& A, const float& B) { return A > B; });
    
    if (PlayersChangedPositions(CurrentPlayerProgressesMap))
    {
        PlayerProgressesMap = CurrentPlayerProgressesMap;
        UpdatePlayerPositions();
	}
}

void AG_RaceTrajectorySpline::UpdateActorsInWorld()
{
    AGameStateBase* GameState = GetWorld()->GetGameState();
    if (!GameState) return;

    int PlayersNum = 0;
    for (auto& PlayerState : GameState->PlayerArray)
    {
        if (AG_RacePlayerState* RacePlayerState = Cast<AG_RacePlayerState>(PlayerState))
        {
            if (!RacePlayerState->GetFinishedRace())
            {
                PlayersNum += 1;
            }
        }
    }

    if (PlayersNum != ActorsInWorld.Num())
    {
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), AG_Character::StaticClass(), ActorsInWorld);
    }
}

TMap<AActor*, float> AG_RaceTrajectorySpline::GetUpdatedPlayerProgressess()
{
    TMap<AActor*, float> Players;
    for (AActor* Actor : ActorsInWorld)
    {
        if (Actor)
        {
            Players.Add(Actor, GetPlayerProgress(Actor));
        }
    }
    return Players;
}

bool AG_RaceTrajectorySpline::PlayersChangedPositions(TMap<AActor*, float>& CurrentPlayerProgressesMap)
{
    TArray<AActor*> Keys1, Keys2;
    CurrentPlayerProgressesMap.GetKeys(Keys1);
    PlayerProgressesMap.GetKeys(Keys2);
    return Keys1 != Keys2;
}

void AG_RaceTrajectorySpline::UpdatePlayerPositions()
{
    if (!HasAuthority()) return;

    int Place = 1;
    for (auto& Player : PlayerProgressesMap)
    {
        AG_Character* Character = Cast<AG_Character>(Player.Key);
        if (Character)
        {
            AG_RacePlayerController* PlayerController = Character->GetController<AG_RacePlayerController>();
            if (PlayerController)
            {
                PlayerController->SetPlayerPosition(Place);
                Place += 1;
            }
        }
    }
}


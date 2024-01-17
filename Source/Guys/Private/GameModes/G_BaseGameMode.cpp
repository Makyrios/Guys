// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameModes/G_BaseGameMode.h"
#include "Characters/G_Character.h"
#include "UObject/ConstructorHelpers.h"
#include <Kismet/GameplayStatics.h>
#include <Misc/G_PlayerStart.h>

void AG_BaseGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);

    if (bDelayedStart)
    {
        GetWorldTimerManager().SetTimer(DelayStartTimer, this, &AG_BaseGameMode::StartMatch, DelayBeforeStart);
    }
}

bool AG_BaseGameMode::ReadyToStartMatch_Implementation()
{
    if (bDelayedStart) return false;

    if (GetMatchState() == MatchState::WaitingToStart)
    {
        return !GetWorldTimerManager().IsTimerActive(DelayStartTimer);
    }
    return false;
}

void AG_BaseGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    /* TODO
    AAS_BasePlayerState* PlayerState = NewPlayer->GetPlayerState<AAS_BasePlayerState>();
    UAS_GameInstance* GameInstance = Cast<UAS_GameInstance>(GetGameInstance());

    if (GameInstance && PlayerState)
    {
        const FString PlayerName = GameInstance->GetPlayerName().ToString();
        PlayerState->SetPlayerName(PlayerName);
    }
    CreateStartGameWidget(NewPlayer);*/
}

void AG_BaseGameMode::CreateStartGameWidget(APlayerController* NewPlayer)
{
    /* TODO
    if (AAS_PlayerController* CustomPlayerController = Cast<AAS_PlayerController>(NewPlayer))
    {
        if (!IsGameStarted())
        {
            const float CurrentDelayBeforeStart = DelayBeforeStart - GameState->GetServerWorldTimeSeconds();
            CustomPlayerController->CreateStartGameWidget(CurrentDelayBeforeStart);
        }
    }*/
}

void AG_BaseGameMode::HandleMatchHasStarted()
{
    Super::HandleMatchHasStarted();

    for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
    {
        const AActor* PlayerStart = ChoosePlayerStart_Implementation(Iterator->Get());
        APawn* PlayerPawn = (*Iterator)->GetPawn();
        if (PlayerStart && PlayerPawn)
        {
            PlayerPawn->SetActorLocation(PlayerStart->GetActorLocation());
            PlayerPawn->SetActorRotation(PlayerStart->GetActorRotation());
        }
        /* TODO
        if (AAS_PlayerController* CustomPlayerController = Cast<AAS_PlayerController>(*Iterator))
        {
            CustomPlayerController->SetHUDWidgetVisibility(ESlateVisibility::Visible);
            CustomPlayerController->SetScoreGoal(ScoreGoal);
        }*/
    }
}

AActor* AG_BaseGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
    if (!Player) return nullptr;

    TArray<AActor*> PlayerStarts;
    UGameplayStatics::GetAllActorsOfClass(this, AG_PlayerStart::StaticClass(), PlayerStarts);

    TArray<AG_PlayerStart*> ValidPlayerStarts;
    for (int i = 0; i < PlayerStarts.Num(); ++i)
    {
        AG_PlayerStart* CustomPlayerStart = Cast<AG_PlayerStart>(PlayerStarts[i]);
        if (!(CustomPlayerStart->GetIsOccupied()))
        {
            ValidPlayerStarts.AddUnique(CustomPlayerStart);
        }
    }

    if (ValidPlayerStarts.IsEmpty()) return nullptr;

    const int32 RandIndex = FMath::RandRange(0, ValidPlayerStarts.Num() - 1);
    ValidPlayerStarts[RandIndex]->SetIsOccupied(true);

    return ValidPlayerStarts[RandIndex];
}

void AG_BaseGameMode::HandleActorDeath(AController* DeadActor)
{
    if (!DeadActor) return;

    FTimerHandle DelayRespawnTimer;
    RespawnDelegate.BindUFunction(this, FName("RespawnPawn"), DeadActor);
    GetWorldTimerManager().SetTimer(DelayRespawnTimer, RespawnDelegate, MinRespawnDelay, false);
}

void AG_BaseGameMode::RespawnPawn(AController* Controller)
{
    UWorld* World = GetWorld();
    APawn* OldPawn = Controller->GetPawn();
    const AActor* PlayerStart = ChoosePlayerStart_Implementation(Controller);

    if (!World || !Controller || !OldPawn || !PlayerStart) return;

    AG_Character* NewPawn =
        World->SpawnActor<AG_Character>(OldPawn->GetClass(), PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation());

    OldPawn->Destroy();

    if (NewPawn)
    {
        Controller->UnPossess();
        Controller->Possess(NewPawn);
    }
}

bool AG_BaseGameMode::ReadyToEndMatch_Implementation()
{
    /* TODO
    if (const AAS_BaseGameState* CurrentGameState = Cast<AAS_BaseGameState>(GameState))
    {
        return CurrentGameState->ElapsedTime >= TimeLimit;
    }
    return false;*/
    return false;
}

void AG_BaseGameMode::HandleMatchHasEnded()
{
    Super::HandleMatchHasEnded();

    UWorld* World = GetWorld();
    if (!World) return;

    UGameplayStatics::SetGlobalTimeDilation(this, 0.3);

    FTimerHandle OpenLevelTimer;
    FTimerDelegate OpenLevelDelegate;
    OpenLevelDelegate.BindUObject(this, &AG_BaseGameMode::RestartGame);

    World->GetTimerManager().SetTimer(OpenLevelTimer, OpenLevelDelegate, DelayBeforeRestart, false);
}

void AG_BaseGameMode::RestartGame()
{
    UWorld* World = GetWorld();
    if (!World) return;

    const FString MapName = UGameplayStatics::GetCurrentLevelName(World);
    World->ServerTravel(MapName);
}

bool AG_BaseGameMode::IsGameStarted()
{
    UWorld* World = GetWorld();
    if (!World) return false;

    return !(World->GetTimerManager().IsTimerActive(DelayStartTimer));
}

// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameModes/G_BaseGameMode.h"
#include "Character/G_Character.h"
#include "UObject/ConstructorHelpers.h"
#include <Kismet/GameplayStatics.h>
#include <Misc/G_PlayerStart.h>
#include <Player/G_PlayerState.h>
#include "Actors/G_Checkpoint.h"
#include <GameInstance/G_GameInstance.h>
#include <Player/G_PlayerController.h>
#include "GameFramework/GameStateBase.h"
#include "Components/SlateWrapperTypes.h"

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

    AG_PlayerState* PlayerState = NewPlayer->GetPlayerState<AG_PlayerState>();
    UG_GameInstance* GameInstance = Cast<UG_GameInstance>(GetGameInstance());

    if (GameInstance && PlayerState)
    {
        const FString PlayerName = GameInstance->GetPlayerName().ToString();
        PlayerState->SetPlayerName(PlayerName);
    }
    CreateStartGameWidget(NewPlayer);
}

void AG_BaseGameMode::CreateStartGameWidget(APlayerController* NewPlayer)
{
    if (AG_PlayerController* CustomPlayerController = Cast<AG_PlayerController>(NewPlayer))
    {
        if (!IsGameStarted())
        {
            const float CurrentDelayBeforeStart = DelayBeforeStart - GameState->GetServerWorldTimeSeconds();
            CustomPlayerController->CreateStartGameWidget(CurrentDelayBeforeStart);
        }
    }
}

void AG_BaseGameMode::HandleMatchHasStarted()
{
    Super::HandleMatchHasStarted();

    for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
    {
        MovePawnToRandomPlayerStart(Iterator);
        ShowHUDWidget(Iterator);
    }
}

void AG_BaseGameMode::MovePawnToRandomPlayerStart(FConstPlayerControllerIterator& Iterator)
{
    const AActor* PlayerStart = ChoosePlayerStart_Implementation(Iterator->Get());
    APawn* PlayerPawn = (*Iterator)->GetPawn();
    if (PlayerStart && PlayerPawn)
    {
        PlayerPawn->SetActorLocation(PlayerStart->GetActorLocation());
        PlayerPawn->SetActorRotation(PlayerStart->GetActorRotation());
    }
}

void AG_BaseGameMode::ShowHUDWidget(FConstPlayerControllerIterator& Iterator)
{
    if (AG_PlayerController* CustomPlayerController = Cast<AG_PlayerController>(*Iterator))
    {
        CustomPlayerController->SetHUDWidgetVisibility(ESlateVisibility::Visible);
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

    AActor* PlayerStart = ChoosePlayerStart_Implementation(Controller);

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
    return false;
}

void AG_BaseGameMode::HandleMatchHasEnded()
{
    Super::HandleMatchHasEnded();

    UWorld* World = GetWorld();
    if (!World) return;

    /*
    UGameplayStatics::SetGlobalTimeDilation(this, 0.3);
    */
    UGameplayStatics::SetGamePaused(this, true);

    FTimerHandle OpenLevelTimer;

    World->GetTimerManager().SetTimer(OpenLevelTimer, [this]() {RestartGame(); }, DelayBeforeRestart, false);
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

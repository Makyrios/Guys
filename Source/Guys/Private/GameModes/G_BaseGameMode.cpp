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
#include "GameFramework/SpectatorPawn.h"
#include <Actors/G_SpectatorPawn.h>
#include <GameFramework/GameState.h>

void AG_BaseGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);
}

void AG_BaseGameMode::HandleSeamlessTravelPlayer(AController*& C)
{
    Super::HandleSeamlessTravelPlayer(C);

    /*LoadedPlayers += 1;
    if (LoadedPlayers == GetNumExpectedPlayers())
    {
        OnAllPlayersLoaded();
    }*/

    /*if (bDelayedStart)
    {
        GetWorldTimerManager().SetTimer(DelayStartTimer, this, &AG_BaseGameMode::StartMatch, DelayBeforeStart);
    }*/
}

int32 AG_BaseGameMode::GetNumExpectedPlayers() const
{
    if (UG_GameInstance* GameInstance = GetGameInstance<UG_GameInstance>())
    {
        return GameInstance->GetNumExpectedPlayers();
    }
    return 0;
}

void AG_BaseGameMode::SetMatchState(FName NewMatchState)
{
    Super::SetMatchState(NewMatchState);

    OnChangeMatchState.Broadcast(NewMatchState);
    if (NewMatchState != GetMatchState())
    {
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

    LoadedPlayers += 1;
    if (LoadedPlayers >= GetNumExpectedPlayers())
    {
        OnAllPlayersLoaded();
    }

    if (IsMatchPreparing())
    {
        HandleLoginBeforeGameStart(NewPlayer);
    }
    else if (IsMatchStarted())
    {
        HandleLoginAfterGameStart(NewPlayer);
    }
}

void AG_BaseGameMode::OnAllPlayersLoaded()
{
    if (bDelayedStart)
    {
        if (GetWorldTimerManager().IsTimerActive(DelayStartTimer)) return;

        GetWorldTimerManager().SetTimer(
            DelayStartTimer, this, &AG_BaseGameMode::StartMatch, DelayBeforeStart);
        // GetWorldTimerManager().SetTimer(DelayStartTimer, this, &AG_BaseGameMode::StartMatch, DelayBeforeStart);
    }
    else
    {
        StartMatch();
    }
}

bool AG_BaseGameMode::IsMatchPreparing()
{
    return GetMatchState() == MatchState::WaitingToStart || GetMatchState() == MatchState::EnteringMap;
}

bool AG_BaseGameMode::IsMatchStarted()
{
    return GetMatchState() == MatchState::InProgress;
}

void AG_BaseGameMode::HandleLoginBeforeGameStart(APlayerController* NewPlayer) {}

void AG_BaseGameMode::HandleLoginAfterGameStart(APlayerController* NewPlayer) {}

void AG_BaseGameMode::SpawnNewPawn(APlayerController* NewPlayer)
{
    if (!NewPlayer) return;
    APawn* NewPawn = GetWorld()->SpawnActor<APawn>(DefaultPawnClass);
    NewPlayer->Possess(NewPawn);
    MovePawnToRandomPlayerStart(NewPawn);
}

void AG_BaseGameMode::SetControllerMatchState(APlayerController* PlayerController, FName NewMatchState)
{
    if (AG_PlayerController* CustomPlayerController = Cast<AG_PlayerController>(PlayerController))
    {
        CustomPlayerController->SetCurrentMatchState(NewMatchState);
    }
}

void AG_BaseGameMode::EnableSpectatorHUD(APlayerController* NewPlayer)
{
    if (AG_PlayerController* CustomPlayerController = Cast<AG_PlayerController>(NewPlayer))
    {
        CustomPlayerController->SetSpectatorHUD(true);
    }
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

void AG_BaseGameMode::SpawnSpectatorPawn(APlayerController* NewPlayer)
{
    if (!NewPlayer) return;

    APawn* SpectatorPawn = GetWorld()->SpawnActor<APawn>(SpectatorClass, NewPlayer->GetSpawnLocation(), NewPlayer->GetControlRotation());
    NewPlayer->Possess(SpectatorPawn);
}

void AG_BaseGameMode::HandleMatchIsWaitingToStart()
{
    Super::HandleMatchIsWaitingToStart();

    /*for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
    {
        if (Iterator)
        {
            SetControllerMatchState(Iterator->Get(), GetMatchState());
        }
    }*/
}

void AG_BaseGameMode::HandleMatchHasStarted()
{
    Super::HandleMatchHasStarted();

    for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
    {
        if (Iterator)
        {
            //SetControllerMatchState(Iterator->Get(), GetMatchState());
            //ShowHUDWidget(Iterator->Get());
        }
    }
}

void AG_BaseGameMode::MovePawnToRandomPlayerStart(APawn* PawnToMove)
{
    const AActor* PlayerStart = ChoosePlayerStart();
    if (PlayerStart && PawnToMove)
    {
        PawnToMove->SetActorLocation(PlayerStart->GetActorLocation());
        PawnToMove->SetActorRotation(PlayerStart->GetActorRotation());
    }
}

void AG_BaseGameMode::ShowHUDWidget(APlayerController* PlayerController)
{
    if (AG_PlayerController* CustomPlayerController = Cast<AG_PlayerController>(PlayerController))
    {
        CustomPlayerController->SetHUDWidgetVisibility(ESlateVisibility::Visible);
    }
}

AActor* AG_BaseGameMode::ChoosePlayerStart()
{
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

    AActor* PlayerStart = ChoosePlayerStart();

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

    FTimerHandle OpenLevelTimer;

    World->GetTimerManager().SetTimer(
        OpenLevelTimer, [this]() { RestartGame(); }, DelayBeforeRestart, false);
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

// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/G_LobbyGameMode.h"
#include <GameInstance/G_GameInstance.h>
#include "GameFramework/GameStateBase.h"
#include <Player/G_PlayerController.h>
#include "MultiplayerSubsystem.h"
#include <GameStates/G_LobbyGameState.h>

void AG_LobbyGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);

    LobbyGameState = LobbyGameState.IsValid() ? LobbyGameState : GetGameState<AG_LobbyGameState>();
}

void AG_LobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();

    UG_GameInstance* GameInstance = GetGameInstance<UG_GameInstance>();
    if (GameInstance)
    {
        UMultiplayerSubsystem* Subsystem = GameInstance->GetSubsystem<UMultiplayerSubsystem>();
        check(Subsystem);

        UpdatePlayers(NumberOfPlayers, Subsystem->DesiredNumPublicConnections);

        if (NumberOfPlayers == Subsystem->DesiredNumPublicConnections)
        {
            GameInstance->SetNumExpectedPlayers(NumberOfPlayers);
            StartChangeMapTimer(Subsystem);
            OnMinPlayersReached();
        }
    }
}

void AG_LobbyGameMode::OnMinPlayersReached()
{
    LobbyGameState = LobbyGameState.IsValid() ? LobbyGameState : GetGameState<AG_LobbyGameState>();
    if (LobbyGameState.IsValid())
    {
        LobbyGameState->SetMinPlayersReached(true);
    }
}

void AG_LobbyGameMode::UpdatePlayers(int ConnectedPlayers, int DesiredPlayersNum)
{
    LobbyGameState = LobbyGameState.IsValid() ? LobbyGameState : GetGameState<AG_LobbyGameState>();
    if (LobbyGameState.IsValid())
    {
        LobbyGameState->OnPlayersUpdate.Broadcast(ConnectedPlayers, DesiredPlayersNum);
    }
}

void AG_LobbyGameMode::StartChangeMapTimer(UMultiplayerSubsystem* Subsystem)
{
    if (!Subsystem)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Subsystem is null"));
        return;
    }

    FTimerHandle ChangeMapHandle;
    FTimerDelegate ChangeMapDelegate = FTimerDelegate::CreateUObject(this, &AG_LobbyGameMode::ChangeMap, Subsystem);

    GetWorld()->GetTimerManager().SetTimer(
        ChangeMapHandle, ChangeMapDelegate, ChangeMapDelay, false);
}

void AG_LobbyGameMode::ChangeMap(UMultiplayerSubsystem* Subsystem)
{
    if (!Subsystem)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Subsystem is null in changemap"));
        return;
    }
    UWorld* World = GetWorld();
    if (World)
    {
        bUseSeamlessTravel = true;

        FString MatchType = Subsystem->DesiredMatchType;
        FString PathToMap = MapsForModes.Find(MatchType)->Append("?listen");
        World->ServerTravel(PathToMap);
    }
}

int32 AG_LobbyGameMode::GetNumExpectedPlayers() const
{
    if (GameState)
    {
        return GameState->PlayerArray.Num();
    }
    return 0;
}

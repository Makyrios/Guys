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
}

void AG_LobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();

    UGameInstance* GameInstance = GetGameInstance();
    if (GameInstance)
    {
        UMultiplayerSubsystem* Subsystem = GameInstance->GetSubsystem<UMultiplayerSubsystem>();
        check(Subsystem);

        if (NumberOfPlayers == Subsystem->DesiredNumPublicConnections)
        {
            StartChangeMapTimer(Subsystem);
            OnMinPlayersReached();
        }
    }
}

void AG_LobbyGameMode::StartChangeMapTimer(UMultiplayerSubsystem* Subsystem)
{
    FTimerHandle ChangeMapHandle;

    GetWorld()->GetTimerManager().SetTimer(
        ChangeMapHandle, [&]() { ChangeMap(Subsystem); }, ChangeMapDelay, false);
}

void AG_LobbyGameMode::OnMinPlayersReached()
{
    if (AG_LobbyGameState* LobbyGameState = GetGameState<AG_LobbyGameState>())
    {
        LobbyGameState->SetMinPlayersReached(true);
    }
}

void AG_LobbyGameMode::ChangeMap(UMultiplayerSubsystem* Subsystem)
{
    if (!Subsystem) return;
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

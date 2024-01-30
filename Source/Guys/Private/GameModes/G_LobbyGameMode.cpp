// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/G_LobbyGameMode.h"
#include <GameInstance/G_GameInstance.h>
#include "GameFramework/GameStateBase.h"
#include <Player/G_PlayerController.h>

void AG_LobbyGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);

    FTimerHandle ChangeMapHandle;

    GetWorld()->GetTimerManager().SetTimer(
        ChangeMapHandle, [this]() { MapChange(FName("ThirdPersonMap")); }, 10, false);
}

// IS CALLED BEFORE PAWN POSSSESS. MOVE???
void AG_LobbyGameMode::HandleLoginAfterGameStart(APlayerController* NewPlayer)
{
    if (AG_PlayerController* CustomPlayerController = Cast<AG_PlayerController>(NewPlayer))
    {
        CustomPlayerController->SetKeyboardInput(true);
    }
}

void AG_LobbyGameMode::MapChange(FName MapName)
{
    if (UG_GameInstance* GameInstance = GetGameInstance<UG_GameInstance>())
    {
        int32 NumExpectedPlayers = GetNumExpectedPlayers();
        GameInstance->SetNumExpectedPlayers(NumExpectedPlayers);
    }
    GetWorld()->ServerTravel(MapName.ToString());
}

int32 AG_LobbyGameMode::GetNumExpectedPlayers() const
{
    if (GameState)
    {
        return GameState->PlayerArray.Num();
    }
    return 0;
}

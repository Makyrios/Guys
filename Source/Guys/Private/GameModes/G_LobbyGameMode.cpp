// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/G_LobbyGameMode.h"
#include <GameInstance/G_GameInstance.h>
#include "GameFramework/GameStateBase.h"
#include <Player/G_PlayerController.h>
#include "MultiplayerSubsystem.h"

void AG_LobbyGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);

    /*FTimerHandle ChangeMapHandle;

    GetWorld()->GetTimerManager().SetTimer(
        ChangeMapHandle, [this]() { MapChange(FName("ThirdPersonMap")); }, 10, false);*/
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
            UWorld* World = GetWorld();
            if (World)
            {
                bUseSeamlessTravel = true;

                FString MatchType = Subsystem->DesiredMatchType;
                //FString PathToMap = FString::Printf(TEXT("%s?listen"), MapsForModes.Find(MatchType));
                FString PathToMap = MapsForModes.Find(MatchType)->Append("?listen");
                World->ServerTravel(PathToMap);
            }
        }
    }
}

//void AG_LobbyGameMode::HandleLoginAfterGameStart(APlayerController* NewPlayer)
//{
//    Super::HandleLoginAfterGameStart(NewPlayer);
//}

int32 AG_LobbyGameMode::GetNumExpectedPlayers() const
{
    if (GameState)
    {
        return GameState->PlayerArray.Num();
    }
    return 0;
}

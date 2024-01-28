// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/G_LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "MultiplayerSubsystem.h"

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
				FString PathToMap = FString::Printf(TEXT("%s?listen"), MapsForModes.Find(MatchType));
				World->ServerTravel(PathToMap);
			}
		}
	}
}

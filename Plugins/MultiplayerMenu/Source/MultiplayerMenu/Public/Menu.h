// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Menu.generated.h"

class UButton;
class UMultiplayerSubsystem;
/**
 * 
 */
UCLASS()
class MULTIPLAYERMENU_API UMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void MenuSetup(int32 NumberOfPublicConnections = 4, FString TypeOfMatch = FString(TEXT("Race")), FString LobbyPath = FString(TEXT("Game/ThirdPerson/Maps/LobbyMap")));

protected:
	virtual bool Initialize() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);
	void OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);
	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);
	UFUNCTION()
	void OnStartSession(bool bWasSuccessful);

private:
	UFUNCTION()
	void HostButtonClicked();

	void MenuTearDown();

public:
	UPROPERTY(BlueprintReadWrite)
	int32 PublicConnectionsNum;

	UPROPERTY(BlueprintReadWrite)
	FString MatchType;

	FString PathToLobby;

private:
	UPROPERTY(meta = (BindWidget))
	UButton* HostButton;

	UMultiplayerSubsystem* MultiplayerSubsystem;
};

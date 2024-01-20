// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "G_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GUYS_API UG_GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;

	UFUNCTION()
	virtual void BeginLoadingScreen(const FString& MapName);

	UFUNCTION()
	virtual void EndLoadingScreen(UWorld* InLoadedWorld);

	FORCEINLINE void SetPlayerName(FText NewName) { PlayerName = NewName; }
	FORCEINLINE FText GetPlayerName() const { return PlayerName; }

public:
	UPROPERTY(EditDefaultsOnly, Category = "AS|LoadingScreen")
	TSubclassOf<UUserWidget> LoadingScreenClass;

	FText PlayerName = FText::FromString(TEXT("Player"));
};

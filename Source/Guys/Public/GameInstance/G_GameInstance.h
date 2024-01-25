// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "G_GameInstance.generated.h"

class USoundClass;

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

    void SetMasterSoundVolume(float Volume);
    float GetMasterSoundVolume() const;

    FORCEINLINE FName GetMenuMapName() const { return MenuMapName; }

private:
    UPROPERTY(EditDefaultsOnly, Category = "G|LoadingScreen")
    TSubclassOf<UUserWidget> LoadingScreenClass;

    UPROPERTY(EditDefaultsOnly, Category = "G|Maps")
    FName MenuMapName;

    UPROPERTY(EditDefaultsOnly, Category = "G|Sound")
    TObjectPtr<USoundClass> MasterSoundClass;

    FText PlayerName = FText::FromString(TEXT("Player"));
};

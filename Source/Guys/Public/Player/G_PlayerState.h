// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "G_PlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class AG_Checkpoint;

UCLASS()
class GUYS_API AG_PlayerState : public APlayerState, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    AG_PlayerState();

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    UAttributeSet* GetAttributeSet() const;

    FORCEINLINE void AddPlayerScore(int32 ScoreToAdd) { PlayerScore += ScoreToAdd; }
    FORCEINLINE int32 GetPlayerScore() const { return PlayerScore; }

    FORCEINLINE void SetLastCheckpoint(TWeakObjectPtr<AG_Checkpoint> Checkpoint) { LastCheckpoint = Checkpoint; }
    FORCEINLINE TWeakObjectPtr<AG_Checkpoint> GetLastCheckpoint() const { return LastCheckpoint; }

protected:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    UPROPERTY()
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

    UPROPERTY()
    TObjectPtr<UAttributeSet> AttributeSet;

protected:
    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "G|Stats")
    int32 PlayerScore = 0;

    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "G|Stats")
    FString PlayerName = "";

    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "G|Spawn")
    TWeakObjectPtr<AG_Checkpoint> LastCheckpoint;
};

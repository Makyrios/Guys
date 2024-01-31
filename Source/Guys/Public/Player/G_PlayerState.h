// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "Character/G_Character.h"
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

protected:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    UPROPERTY()
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

    UPROPERTY()
    TObjectPtr<UAttributeSet> AttributeSet;

protected:
    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "G|Stats")
    FString PlayerName = "";

    UPROPERTY()
    TObjectPtr<AG_Character> Character{nullptr};
};

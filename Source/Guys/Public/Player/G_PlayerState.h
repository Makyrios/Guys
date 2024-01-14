// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "G_PlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
/**
 *
 */
UCLASS()
class GUYS_API AG_PlayerState : public APlayerState, public IAbilitySystemInterface
{
    GENERATED_BODY()
public:
    AG_PlayerState();

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    UAttributeSet* GetAttributeSet() const;

protected:
    UPROPERTY()
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

    UPROPERTY()
    TObjectPtr<UAttributeSet> AttributeSet;
};

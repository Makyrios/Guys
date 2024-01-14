// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/G_PlayerState.h"

#include "AbilitySystem/G_AbilitySystemComponent.h"
#include "AbilitySystem/G_AttributeSet.h"

AG_PlayerState::AG_PlayerState()
{
    NetUpdateFrequency = 100.0f;

    AbilitySystemComponent = CreateDefaultSubobject<UG_AbilitySystemComponent>("AbilitySystemComponent");
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

    AttributeSet = CreateDefaultSubobject<UG_AttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AG_PlayerState::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

UAttributeSet* AG_PlayerState::GetAttributeSet() const
{
    return AttributeSet;
}

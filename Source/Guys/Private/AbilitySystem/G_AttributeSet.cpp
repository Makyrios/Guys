// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/G_AttributeSet.h"

#include "Net/UnrealNetwork.h"

UG_AttributeSet::UG_AttributeSet()
{
    InitScore(0.0f);
    Name = "None";
}

void UG_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION_NOTIFY(UG_AttributeSet, Score, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UG_AttributeSet, Name, COND_None, REPNOTIFY_Always);
}

void UG_AttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);
}

void UG_AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);
}

void UG_AttributeSet::OnRep_Score(const FGameplayAttributeData& OldScore) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UG_AttributeSet, Score, OldScore);
}

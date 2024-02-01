// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/G_AttributeSet.h"

#include "Character/G_Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"

UG_AttributeSet::UG_AttributeSet()
{
    InitMaxMovementSpeed(300.0f);
    InitJumpCooldown(0.5f);
    InitInteractCooldown(2.0f);
}

void UG_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    /*DOREPLIFETIME_CONDITION_NOTIFY(UG_AttributeSet, MaxMovementSpeed, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UG_AttributeSet, JumpCooldown, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UG_AttributeSet, InteractCooldown, COND_None, REPNOTIFY_Always);*/
}

void UG_AttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);
}

void UG_AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);
}

void UG_AttributeSet::OnRep_MaxMovementSpeed(const FGameplayAttributeData& OldMaxMovementSpeed) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UG_AttributeSet, MaxMovementSpeed, OldMaxMovementSpeed);
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/G_AbilitySystemComponent.h"

void UG_AbilitySystemComponent::AbilityActorInfoSet()
{
    OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UG_AbilitySystemComponent::EffectApplied);
}

void UG_AbilitySystemComponent::EffectApplied(
    UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
    FGameplayTagContainer TagContainer;
    EffectSpec.GetAllAssetTags(TagContainer);

    EffectAssetTags.Broadcast(TagContainer);
}

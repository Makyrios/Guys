// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "G_AbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer&);

/**
 *
 */
UCLASS()
class GUYS_API UG_AbilitySystemComponent : public UAbilitySystemComponent
{
    GENERATED_BODY()
public:
    void AbilityActorInfoSet();

    FEffectAssetTags EffectAssetTags;

protected:
    void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec,
        FActiveGameplayEffectHandle ActiveEffectHandle);
};

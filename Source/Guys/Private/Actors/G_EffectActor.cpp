// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/G_EffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AG_EffectActor::AG_EffectActor()
{
    PrimaryActorTick.bCanEverTick = false;

    SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AG_EffectActor::BeginPlay()
{
    Super::BeginPlay();
}

void AG_EffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
    UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
    if (TargetASC == nullptr) return;

    check(GameplayEffectClass);

    FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
    EffectContextHandle.AddSourceObject(this);

    const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);
    const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

    const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
    if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
    {
        ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
    }
}

void AG_EffectActor::OnOverlap(AActor* TargetActor)
{
    if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
    {
        for (int i = 0; i < InstantGameplayEffectClasses.Num(); i++)
        {
            ApplyEffectToTarget(TargetActor, InstantGameplayEffectClasses[i]);
        }
    }
    if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
    {
        for (int i = 0; i < DurationGameplayEffectClasses.Num(); i++)
        {
            ApplyEffectToTarget(TargetActor, DurationGameplayEffectClasses[i]);
        }
    }
    if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
    {
        for (int i = 0; i < InfiniteGameplayEffectClasses.Num(); i++)
        {
            ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClasses[i]);
        }
    }
}

void AG_EffectActor::OnEndOverlap(AActor* TargetActor)
{
    if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
    {
        UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
        if (TargetASC == nullptr) return;

        TArray<FActiveGameplayEffectHandle> HandlesToRemove;
        for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)
        {
            if (TargetASC == HandlePair.Value)
            {
                TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
                HandlesToRemove.Add(HandlePair.Key);
            }
        }
        for (FActiveGameplayEffectHandle& Handle : HandlesToRemove)
        {
            ActiveEffectHandles.FindAndRemoveChecked(Handle);
        }
    }
    if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
    {
        for (int i = 0; i < InstantGameplayEffectClasses.Num(); i++)
        {
            ApplyEffectToTarget(TargetActor, InstantGameplayEffectClasses[i]);
        }
    }
    if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
    {
        for (int i = 0; i < DurationGameplayEffectClasses.Num(); i++)
        {
            ApplyEffectToTarget(TargetActor, DurationGameplayEffectClasses[i]);
        }
    }
    if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
    {
        for (int i = 0; i < InfiniteGameplayEffectClasses.Num(); i++)
        {
            ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClasses[i]);
        }
    }
}

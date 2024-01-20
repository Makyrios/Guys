// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "G_EffectActor.generated.h"

class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy
{
    ApplyOnOverlap,
    ApplyOnEndOverlap,
    DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy
{
    RemoveOnEndOverlap,
    DoNotRemove
};

UCLASS()
class GUYS_API AG_EffectActor : public AActor
{
    GENERATED_BODY()
public:
    AG_EffectActor();

protected:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable)
    void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

    UFUNCTION(BlueprintCallable)
    void OnOverlap(AActor* TargetActor);

    UFUNCTION(BlueprintCallable)
    void OnEndOverlap(AActor* TargetActor);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects");
    bool bDestroyOnEffectRemoval = false;

    // Instant

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects");
    TArray<TSubclassOf<UGameplayEffect>> InstantGameplayEffectClasses;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects");
    EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

    // Duration

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects");
    TArray<TSubclassOf<UGameplayEffect>> DurationGameplayEffectClasses;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects");
    EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

    // Infinite

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects");
    TArray<TSubclassOf<UGameplayEffect>> InfiniteGameplayEffectClasses;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects");
    EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects");
    EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;

    //---------

    TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
    float ActorLevel = 1.0f;
};

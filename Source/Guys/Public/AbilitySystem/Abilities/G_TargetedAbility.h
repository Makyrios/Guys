// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "G_TargetedAbility.generated.h"

class UGameplayEffect;
class APawn;
class UNiagaraComponent;

/**
 * 
 */
UCLASS()
class GUYS_API UG_TargetedAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "G|Ability")
	TSubclassOf<UGameplayEffect> EffectToApply;

	UPROPERTY(EditAnywhere, Category = "G|Ability")
	TSubclassOf<UNiagaraComponent> VisualEffect;

	UPROPERTY(BlueprintReadWrite, Category = "G|Target")
	TObjectPtr<APawn> Target;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "G_AttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)                                                                                       \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName)                                                                             \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)                                                                                           \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)                                                                                           \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 *
 */
UCLASS()
class GUYS_API UG_AttributeSet : public UAttributeSet
{
    GENERATED_BODY()
public:
    UG_AttributeSet();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

    // OnRep functions to variables
    UFUNCTION()
    void OnRep_Score(const FGameplayAttributeData& OldScore) const;

public:
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Score, Category = "Multiplayer Attributes")
    FGameplayAttributeData Score;
    ATTRIBUTE_ACCESSORS(UG_AttributeSet, Score);

    UPROPERTY(BlueprintReadWrite, Replicated, Category = "Multiplayer Attributes")
    FString Name;
};

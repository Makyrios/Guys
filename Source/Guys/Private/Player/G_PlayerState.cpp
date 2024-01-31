// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/G_PlayerState.h"
#include "AbilitySystem/G_AbilitySystemComponent.h"
#include "AbilitySystem/G_AttributeSet.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"


AG_PlayerState::AG_PlayerState()
{
    NetUpdateFrequency = 100.0f;

    AbilitySystemComponent = CreateDefaultSubobject<UG_AbilitySystemComponent>("AbilitySystemComponent");
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

    AttributeSet = CreateDefaultSubobject<UG_AttributeSet>("AttributeSet");

    UG_AttributeSet* GAttributeSet = Cast<UG_AttributeSet>(AttributeSet);

    AbilitySystemComponent
        ->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")), EGameplayTagEventType::NewOrRemoved)
        .AddUObject(this, &AG_PlayerState::StunTagChanged);

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GAttributeSet->GetMaxMovementSpeedAttribute())
        .AddUObject(this, &AG_PlayerState::OnMaxMovementSpeedAttributeChanged);
}

void AG_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AG_PlayerState, PlayerName);
}

UAbilitySystemComponent* AG_PlayerState::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

UAttributeSet* AG_PlayerState::GetAttributeSet() const
{
    return AttributeSet;    
}

void AG_PlayerState::OnMaxMovementSpeedAttributeChanged(const FOnAttributeChangeData& Data)
{
    Character = Cast<AG_Character>(GetPawn());

    if (Character == nullptr) return;

    Character->GetCharacterMovement()->MaxWalkSpeed = Data.NewValue;
}

void AG_PlayerState::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
    if (NewCount == 0)
    {
        GetPlayerController()->SetIgnoreMoveInput(false);
    }
    else
    {
        GetPlayerController()->SetIgnoreMoveInput(true);
    }
}
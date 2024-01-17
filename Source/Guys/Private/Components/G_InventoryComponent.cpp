// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/G_InventoryComponent.h"
#include "Abilities/GameplayAbility.h"

// Sets default values for this component's properties
UG_InventoryComponent::UG_InventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UG_InventoryComponent::AddAbility(UGameplayAbility* NewAbility)
{
	OwnedAbilities.Add(NewAbility);

	TWeakObjectPtr<UGameplayAbility> Ability = OwnedAbilities[OwnedAbilities.Find(NewAbility)];

	if (Ability.IsValid())
	{
		// Delegates subscribe here
	}
}

void UG_InventoryComponent::RemoveAbility(const int32& AbilitySlot)
{
	TWeakObjectPtr<UGameplayAbility> Ability = OwnedAbilities[AbilitySlot];

	if (Ability.IsValid())
	{
		// Delegates unsubscribe
	}

	OwnedAbilities.RemoveSingle(Ability);
}

void UG_InventoryComponent::RemoveAllAbilities()
{
	for (TWeakObjectPtr<UGameplayAbility>& Ability : OwnedAbilities)
	{
		if (Ability.IsValid())
		{
			// Delegates unsubscribe
		}
	}

	OwnedAbilities.Empty();
}

bool UG_InventoryComponent::HasAbility()
{
	return OwnedAbilities.Num() > 0;
}

bool UG_InventoryComponent::CanCollectAbilities( UGameplayAbility* Ability)
{
	if (OwnedAbilities.Num() >= MaxAbilities)
	{
		return false;
	}

	return true;
}

bool UG_InventoryComponent::SelectAbility(const int32& CandidateAbilitySlot)
{
	if ((OwnedAbilities.Num() >= CandidateAbilitySlot) && CurrentAbilitySlot != CandidateAbilitySlot)
	{
		if (UGameplayAbility* CurrentAbility = GetCurrentAbility())
		{
			// Delegates unsubscribe
		}

		CurrentAbilitySlot = CandidateAbilitySlot;

		return true;
	}

	return false;
}
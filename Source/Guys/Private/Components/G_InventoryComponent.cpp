#include "Components/G_InventoryComponent.h"
#include "Abilities/GameplayAbility.h"

UG_InventoryComponent::UG_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UG_InventoryComponent::AddAbility(TSubclassOf<UGameplayAbility> NewAbility)
{
	if (OwnedAbilities.Num() < MaxAbilities)
	{
		OwnedAbilities.Add(NewAbility);
	}
}

void UG_InventoryComponent::RemoveAbility(const int32& AbilitySlot)
{
	OwnedAbilities.RemoveAt(AbilitySlot);
}

void UG_InventoryComponent::RemoveAllAbilities()
{
	OwnedAbilities.Empty();
}

bool UG_InventoryComponent::HasAbility()
{
	return OwnedAbilities.Num() > 0;
}

bool UG_InventoryComponent::CanCollectAbilities()
{
	if (OwnedAbilities.Num() >= MaxAbilities)
	{
		return false;
	}

	return true;
}

bool UG_InventoryComponent::SelectAbility(const int32& CandidateAbilitySlot)
{
	if ((OwnedAbilities.Num() > CandidateAbilitySlot) && CurrentAbilitySlot != CandidateAbilitySlot)
	{

		CurrentAbilitySlot = CandidateAbilitySlot;

		return true;
	}

	return false;
}
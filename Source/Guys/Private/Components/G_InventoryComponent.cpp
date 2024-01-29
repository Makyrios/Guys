#include "Components/G_InventoryComponent.h"
#include "Abilities/GameplayAbility.h"

UG_InventoryComponent::UG_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UG_InventoryComponent::AddAbility(TSubclassOf<UGameplayAbility> NewAbility)
{
	OwnedAbilities.Add(NewAbility);

	//TWeakObjectPtr<UGameplayAbility> Ability = OwnedAbilities[OwnedAbilities.Find(NewAbility)];

	//if (Ability.IsValid())
	//{
	//	// Delegates subscribe here
	//}
}

void UG_InventoryComponent::RemoveAbility(const int32& AbilitySlot)
{
	TSubclassOf<UGameplayAbility> Ability = OwnedAbilities[AbilitySlot];

	//if (Ability.IsValid())
	//{
	//	// Delegates unsubscribe
	//}

	OwnedAbilities.RemoveSingle(Ability);
}

void UG_InventoryComponent::RemoveAllAbilities()
{
	//for (TWeakObjectPtr<UGameplayAbility>& Ability : OwnedAbilities)
	//{
	//	if (Ability.IsValid())
	//	{
	//		// Delegates unsubscribe
	//	}
	//}

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
		//if (UGameplayAbility* CurrentAbility = GetCurrentAbility())
		//{
		//	// Delegates unsubscribe
		//}

		CurrentAbilitySlot = CandidateAbilitySlot;

		return true;
	}

	return false;
}
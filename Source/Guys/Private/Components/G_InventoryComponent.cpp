#include "Components/G_InventoryComponent.h"
#include "Abilities/GameplayAbility.h"
#include <Player/G_PlayerController.h>
#include "AbilitySystem/G_AbilitySystemComponent.h"
#include <Player/G_PlayerState.h>
#include "Net/UnrealNetwork.h"

UG_InventoryComponent::UG_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicated(true);
}

void UG_InventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UG_InventoryComponent, OwnedAbilities);
}

void UG_InventoryComponent::AddAbility(TSubclassOf<UGameplayAbility> NewAbility)
{
	if (OwnedAbilities.Num() < MaxAbilities)
	{
		AActor* Owner = GetOwner();
		if (Owner->HasAuthority())
		{
			AG_PlayerController* OwnerController = Cast<AG_PlayerController>(Owner->GetOwner());
			AG_PlayerState* OwnerState = OwnerController->GetPlayerState<AG_PlayerState>();
			FGameplayAbilitySpec AbilitySpec(NewAbility);
			OwnerState->GetAbilitySystemComponent()->GiveAbility(AbilitySpec);
			OwnedAbilities.Add(NewAbility);
		}
	}
	OwnedAbilities.Add(NewAbility);

	AG_PlayerController* PlayerController = GetOwner()->GetInstigatorController<AG_PlayerController>();
    if (PlayerController)
    {
        PlayerController->UpdateAbilityUI(OwnedAbilities);
	}

	//TWeakObjectPtr<UGameplayAbility> Ability = OwnedAbilities[OwnedAbilities.Find(NewAbility)];

	//if (Ability.IsValid())
	//{
	//	// Delegates subscribe here
	//}
}

void UG_InventoryComponent::RemoveAbility(const int32& AbilitySlot)
{
	OwnedAbilities.RemoveAt(AbilitySlot);
	if (OwnedAbilities.Num() > 0)
	{
		CurrentAbilitySlot = FMath::Clamp(CurrentAbilitySlot, 0, OwnedAbilities.Num() - 1);
	}
	else
	{
		CurrentAbilitySlot = 0;
	}

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
	if ((MaxAbilities > CandidateAbilitySlot) && (OwnedAbilities.Num() > CandidateAbilitySlot))
	{

		CurrentAbilitySlot = CandidateAbilitySlot;

		return true;
	}

	return false;
}
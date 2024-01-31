#include "Components/G_InventoryComponent.h"
#include "Abilities/GameplayAbility.h"
#include <Player/G_PlayerController.h>
#include "AbilitySystem/G_AbilitySystemComponent.h"
#include <Player/G_PlayerState.h>
#include "Net/UnrealNetwork.h"

UG_InventoryComponent::UG_InventoryComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UG_InventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UG_InventoryComponent, OwnedAbilities);
    DOREPLIFETIME(UG_InventoryComponent, MaxAbilities);
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
            UpdateAbilityUI();
        }
    }
}

void UG_InventoryComponent::UpdateAbilityUI()
{
    AG_PlayerController* PlayerController = GetOwner()->GetInstigatorController<AG_PlayerController>();
    if (PlayerController)
    {
        FGameplayTagContainer AbilityTags;
        for (auto& Ability : OwnedAbilities)
        {
            if (Ability.GetDefaultObject())
            {
                AbilityTags.AddTagFast(Ability.GetDefaultObject()->AbilityTags.First());
            }
        }
        PlayerController->UpdateAbilityUI(AbilityTags);
    }
}

void UG_InventoryComponent::Server_RemoveAbility_Implementation()
{
    OwnedAbilities.RemoveAt(0);
    UpdateAbilityUI();
}

void UG_InventoryComponent::RemoveAbility(const int32& AbilitySlot)
{
    if (!GetOwner()) return;

    if (!GetOwner()->HasAuthority())
    {
        Server_RemoveAbility();
    }
    else
    {
		OwnedAbilities.RemoveAt(0);
		UpdateAbilityUI();
	}
}

void UG_InventoryComponent::RemoveAllAbilities()
{
    OwnedAbilities.Empty();

    UpdateAbilityUI();
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

bool UG_InventoryComponent::SelectAbility()
{
    if (!GetOwner()) return false;

    if (!GetOwner()->HasAuthority())
    {
		Server_SelectAbility();
	}
    else
    {
        if (OwnedAbilities.Num() == 2)
        {
		    OwnedAbilities.Swap(0, 1);
		    UpdateAbilityUI();
        }
	
    }
    return true;
}


void UG_InventoryComponent::Server_SelectAbility_Implementation()
{
    if (OwnedAbilities.Num() == 2)
    {
        OwnedAbilities.Swap(0, 1);
        UpdateAbilityUI();
    }
}
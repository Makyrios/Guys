// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "G_InventoryComponent.generated.h"

class UGameplayAbility;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GUYS_API UG_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UG_InventoryComponent();

	UFUNCTION(BlueprintCallable, Category = "G|Inventory")
	void AddAbility(UGameplayAbility* NewAbility);

	UFUNCTION(BlueprintCallable, Category = "G|Inventory")
	void RemoveAbility(const int32& AbilitySlot);

	UFUNCTION(BlueprintCallable, Category = "G|Inventory")
	void RemoveAllAbilities();

	UFUNCTION(BlueprintCallable, Category = "G|Inventory")
	bool HasAbility();

	bool CanCollectAbilities(UGameplayAbility* Ability);

	UFUNCTION(BlueprintCallable, Category = "G|Inventory")
	bool SelectAbility(const int32& CandidateAbilitySlot);

	/**
	*  Getter section
	*/
	UFUNCTION(BlueprintCallable, Category = "G|Inventory")
	FORCEINLINE UGameplayAbility* GetAbilityBySlot(const int32& AbilitySlot) const
	{
		return OwnedAbilities[AbilitySlot].IsValid() ? OwnedAbilities[AbilitySlot].Get() : nullptr;
	}

	UFUNCTION(BlueprintCallable, Category = "G|Inventory")
	FORCEINLINE UGameplayAbility* GetCurrentAbility() const
	{
		return OwnedAbilities[CurrentAbilitySlot].IsValid() ? OwnedAbilities[CurrentAbilitySlot].Get() : nullptr;
	}

	TArray<TWeakObjectPtr<UGameplayAbility>> GetOwnedAbilities() { return OwnedAbilities; }

private:
	TArray<TWeakObjectPtr<UGameplayAbility>> OwnedAbilities;

	int32 MaxAbilities;

	int32 CurrentAbilitySlot;
};

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
	void AddAbility(TSubclassOf<UGameplayAbility> NewAbility);

	UFUNCTION(BlueprintCallable, Category = "G|Inventory")
	void RemoveAbility(const int32& AbilitySlot);

	UFUNCTION(BlueprintCallable, Category = "G|Inventory")
	void RemoveAllAbilities();

	UFUNCTION(BlueprintCallable, Category = "G|Inventory")
	bool HasAbility();

	bool CanCollectAbilities();

	UFUNCTION(BlueprintCallable, Category = "G|Inventory")
	bool SelectAbility(const int32& CandidateAbilitySlot);

	/**
	*  Getter section
	*/
	//UFUNCTION(BlueprintCallable, Category = "G|Inventory")
	//FORCEINLINE UGameplayAbility* GetAbilityBySlot(const int32& AbilitySlot) const
	//{
	//	return OwnedAbilities[AbilitySlot].IsValid() ? OwnedAbilities[AbilitySlot].Get() : nullptr;
	//}

	UFUNCTION(BlueprintCallable, Category = "G|Inventory")
	FORCEINLINE TSubclassOf<UGameplayAbility> GetCurrentAbility() const
	{
		return OwnedAbilities.Num() > 0 ? OwnedAbilities[CurrentAbilitySlot] : nullptr;
	}

	TArray<TSubclassOf<UGameplayAbility>> GetOwnedAbilities() { return OwnedAbilities; }

public:
	UPROPERTY(EditAnywhere, Category = "G|Properties")
	int32 MaxAbilities;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "G|Properties")
	int32 CurrentAbilitySlot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "G|Properties")
	TArray<TSubclassOf<UGameplayAbility>> OwnedAbilities;	
};

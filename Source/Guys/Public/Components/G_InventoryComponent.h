#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "G_InventoryComponent.generated.h"

class UGameplayAbility;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GUYS_API UG_InventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UG_InventoryComponent();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

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
    bool SelectAbility();

    UFUNCTION(BlueprintCallable, Category = "G|Inventory")
    FORCEINLINE TSubclassOf<UGameplayAbility> GetCurrentAbility() const
    {
        return OwnedAbilities.Num() > 0 ? OwnedAbilities[0] : nullptr;
    }

    TArray<TSubclassOf<UGameplayAbility>> GetOwnedAbilities() { return OwnedAbilities; }

    void UpdateAbilityUI();

private:
    UFUNCTION(Server, Reliable)
    void Server_RemoveAbility();

    UFUNCTION(Server, Reliable)
    void Server_SelectAbility();

public:
    UPROPERTY(Replicated, EditAnywhere, Category = "G|Properties")
    int32 MaxAbilities = 2;

    UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "G|Properties")
    TArray<TSubclassOf<UGameplayAbility>> OwnedAbilities;
};

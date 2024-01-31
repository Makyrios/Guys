// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Structs/G_ChosenSkinsIdx.h"
#include "Interfaces/G_Interactable.h"
#include "G_Character.generated.h"

class UInputAction;
class UInputMappingContext;
class UAttributeSet;
class USpringArmComponent;
class UCameraComponent;
class AG_PlayerController;
class UG_InventoryComponent;
class UG_PhysicalAnimComponent;
struct FInputActionValue;

UCLASS(config = Game)
class AG_Character : public ACharacter, public IAbilitySystemInterface, public IG_Interactable
{
    GENERATED_BODY()

public:
    AG_Character();

    FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    UAttributeSet* GetAttributeSet() const;

    virtual void PossessedBy(AController* NewController) override;

    virtual void OnRep_PlayerState() override;

    void OnCharacterDie();

    virtual void ReactOnPush(FVector PushDirection) override;

    void SetKeyboardInput(bool bEnable);

    UFUNCTION(Server, Reliable)
    void Server_Interact();

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_Interact(AActor* Actor, FVector Direction);

    FG_ChosenSkinsIdx ChosenSkins;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<TObjectPtr<UMaterialInterface>> Skins;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<TObjectPtr<UStaticMesh>> Hats;

    UPROPERTY()
    TObjectPtr<UStaticMeshComponent> Hat;

    UFUNCTION()
    void UpdateSkins();
    
    UFUNCTION(BlueprintCallable)
    void ChaneSkinByIndex(const int32& Mat_Idx);
    UFUNCTION(NetMulticast, Reliable)
    void SetSkinByIndex(const int32& Mat_Idx);

    UFUNCTION(BlueprintCallable)
    void ChaneHatByIndex(const int32& Hat_Idx);
    UFUNCTION(NetMulticast, Reliable)
    void SetHatByIndex(const int32& Hat_Idx);   
   
    UPROPERTY(BlueprintReadOnly)
    int32 ChosenHatIdx {0};
    UPROPERTY(BlueprintReadOnly)
    int32 ChosenSkinIdx {0};
    
    void CreateSaveFile();
    void SaveSkinsInfo();
    void LoadSkinsInfo();

protected:
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime);

    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    void Move(const FInputActionValue& Value);

    void Look(const FInputActionValue& Value);

    void Jump() override;
    
    void Use();

    void Select();

    void Interact(const FInputActionValue& Value);

    void TogglePause();

    void ToggleStats();


    virtual void InitAbilityActorInfo();

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "G|Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UG_InventoryComponent> InventoryComponent;

protected:
    UPROPERTY()
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

    UPROPERTY()
    TObjectPtr<UAttributeSet> AttributeSet;

private:
    UPROPERTY()
    TWeakObjectPtr<AG_PlayerController> G_PlayerController;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USpringArmComponent> CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UCameraComponent> FollowCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "G|Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UG_PhysicalAnimComponent> PhysicalAnimComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "G|Input", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputMappingContext> DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "G|Input", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputMappingContext> WaitingForGameMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "G|Input", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> JumpAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "G|Input", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "G|Input", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "G|Input", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> InteractAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "G|Input", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> PauseAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "G|Input", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> StatsAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "G|Input", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> UseAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "G|Input", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> SelectAction;

    UPROPERTY()
    FTimerHandle JumpTimer;

    UPROPERTY()
    FTimerHandle InteractTimer;

    UPROPERTY(EditDefaultsOnly, Category = "G|Settings")
    float JumpCooldown = 0.5f;

    UPROPERTY(EditDefaultsOnly, Category = "G|Settings")
    float InteractCooldown = 2.0f;

    UPROPERTY()
    bool bCanInteract = true;

};

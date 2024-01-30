// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interfaces/G_IInteractable.h"
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
class AG_Character : public ACharacter, public IAbilitySystemInterface, public IG_IInteractable
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

    // RENAME
    void SetKeyboardInput(bool bEnable);

    UFUNCTION(Server, Reliable)
    void Server_Interact();

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_Interact(AActor* Actor, FVector Direction);

protected:
    virtual void BeginPlay() override;

    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    void Move(const FInputActionValue& Value);

    void Look(const FInputActionValue& Value);

    void Interact(const FInputActionValue& Value);

    void TogglePause();

    void ToggleStats();

    virtual void Tick(float DeltaTime);

    virtual void InitAbilityActorInfo();

private:
    void ApplyGameplayTags();

    void ApplyAttributes();

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
};

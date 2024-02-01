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
    TArray<TObjectPtr<UMaterialInterface>> Skins;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Skins")
    TArray<TObjectPtr<UStaticMesh>> Hats;

    UPROPERTY()
    TObjectPtr<UStaticMeshComponent> Hat;

    UFUNCTION()
    void UpdateSkins();

    UFUNCTION(BlueprintCallable)
    void ChaneSkinByIndex(int32 Mat_Idx);
    UFUNCTION(NetMulticast, Reliable)
    void SetSkinByIndex(int32 Mat_Idx);

    UFUNCTION(BlueprintCallable)
    void ChaneHatByIndex(int32 Hat_Idx);
    UFUNCTION(NetMulticast, Reliable)
    void SetHatByIndex(int32 Hat_Idx);

    UPROPERTY(BlueprintReadOnly)
    int32 ChosenHatIdx{0};
    UPROPERTY(BlueprintReadOnly)
    int32 ChosenSkinIdx{0};
    FORCEINLINE int32 GetChosenHatIdx() const {return ChosenHatIdx;}
    FORCEINLINE int32 GetChosenSkinIdx() const {return ChosenSkinIdx;}
    void CreateSaveFile();
    void SaveSkinsInfo();
    void LoadSkinsInfo();

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Sound Effects")
    TArray<TObjectPtr<USoundBase>> SoundsOnPush{nullptr};
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Sound Effects")
    TArray<TObjectPtr<USoundBase>> SoundsOnFalling{nullptr};
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Sound Effects")
    TObjectPtr<USoundBase> SoundsOnJump{nullptr};

    UFUNCTION(BlueprintCallable)
    void PlayPunchSound(const FVector& SoundPosition);

    UFUNCTION(BlueprintCallable)
    void PlayFallingSound(const FVector& SoundPosition);
    
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
    
    void UnPossessed() override;
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

    UPROPERTY()
    bool bCanInteract = true;
};

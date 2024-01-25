// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "G_SpectatorPawn.generated.h"

class UInputMappingContext;
class UInputAction;
class AG_PlayerController;
struct FInputActionValue;

UCLASS()
class GUYS_API AG_SpectatorPawn : public ASpectatorPawn
{
    GENERATED_BODY()

protected:
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    void Move(const FInputActionValue& Value);

    void Look(const FInputActionValue& Value);

    void TogglePause();

    void ToggleStats();

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "G|Input", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputMappingContext> SpectatorMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "G|Input", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "G|Input", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "G|Input", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> PauseAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "G|Input", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> StatsAction;


    UPROPERTY()
    TWeakObjectPtr<AG_PlayerController> G_PlayerController;
};

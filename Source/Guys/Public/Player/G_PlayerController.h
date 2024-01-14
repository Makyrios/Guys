// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "G_PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 *
 */
UCLASS()
class GUYS_API AG_PlayerController : public APlayerController
{
    GENERATED_BODY()
public:
    AG_PlayerController();

protected:
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    virtual void SetupInputComponent() override;

private:
    void Move(const FInputActionValue& Value);

    void Look(const FInputActionValue& Value);

    void Jump();

    void StopJumping();

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputMappingContext> DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> JumpAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> LookAction;
};

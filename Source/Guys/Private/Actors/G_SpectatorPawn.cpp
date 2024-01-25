// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/G_SpectatorPawn.h"
#include <EnhancedInputComponent.h>
#include "Player/G_PlayerController.h"

void AG_SpectatorPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &AG_SpectatorPawn::TogglePause);
        EnhancedInputComponent->BindAction(StatsAction, ETriggerEvent::Started, this, &AG_SpectatorPawn::ToggleStats);
        EnhancedInputComponent->BindAction(StatsAction, ETriggerEvent::Completed, this, &AG_SpectatorPawn::ToggleStats);
    }
}

void AG_SpectatorPawn::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(ForwardDirection, MovementVector.Y);
        AddMovementInput(RightDirection, MovementVector.X);
    }
}

void AG_SpectatorPawn::Look(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

void AG_SpectatorPawn::TogglePause()
{
    G_PlayerController = G_PlayerController.IsValid() ? G_PlayerController : Cast<AG_PlayerController>(Controller);
    if (!G_PlayerController.IsValid()) return;

    G_PlayerController->TogglePause();
}

void AG_SpectatorPawn::ToggleStats()
{
    G_PlayerController = G_PlayerController.IsValid() ? G_PlayerController : Cast<AG_PlayerController>(Controller);
    if (!G_PlayerController.IsValid()) return;

    G_PlayerController->ToggleStats();
}

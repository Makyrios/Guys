// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/G_PlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"

AG_PlayerController::AG_PlayerController()
{
    bReplicates = true;
}

void AG_PlayerController::BeginPlay()
{
    Super::BeginPlay();

    check(DefaultMappingContext);

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(DefaultMappingContext, 0);
    }
}

void AG_PlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AG_PlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
    {
        // Jumping
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AG_PlayerController::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AG_PlayerController::StopJumping);

        // Moving
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AG_PlayerController::Move);

        // Looking
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AG_PlayerController::Look);
    }
}

void AG_PlayerController::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    const FRotator Rotation = GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);

    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    if (APawn* ControlledPawn = GetPawn<APawn>())
    {
        ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
        ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
    }
}

void AG_PlayerController::Look(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (APawn* ControlledPawn = GetPawn<APawn>())
    {
        ControlledPawn->AddControllerYawInput(LookAxisVector.X);
        ControlledPawn->AddControllerPitchInput(LookAxisVector.Y);
    }
}

void AG_PlayerController::Jump()
{
    GetPawn<ACharacter>()->Jump();
}

void AG_PlayerController::StopJumping()
{
    GetPawn<ACharacter>()->StopJumping();
}
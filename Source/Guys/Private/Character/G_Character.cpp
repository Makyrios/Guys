// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/G_Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/G_AbilitySystemComponent.h"
#include "AbilitySystem/G_AttributeSet.h"
#include "Player/G_PlayerState.h"
#include "Interfaces/G_IInteractable.h"
#include "Kismet/KismetSystemLibrary.h"
#include <GameModes/G_BaseGameMode.h>
#include "Player/G_PlayerController.h"

AG_Character::AG_Character()
{
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

    FollowCamera->bUsePawnControlRotation = false;
}

void AG_Character::BeginPlay()
{
    Super::BeginPlay();
}

void AG_Character::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    ApplyAttributes();
    ApplyGameplayTags();
}

void AG_Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AG_Character::Move);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AG_Character::Look);
        EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AG_Character::Interact);
        EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &AG_Character::TogglePause);
        EnhancedInputComponent->BindAction(StatsAction, ETriggerEvent::Started, this, &AG_Character::ToggleStats);
        EnhancedInputComponent->BindAction(StatsAction, ETriggerEvent::Completed, this, &AG_Character::ToggleStats);
    }
}

void AG_Character::Move(const FInputActionValue& Value)
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

void AG_Character::Look(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

void AG_Character::Interact(const FInputActionValue& Value)
{
    UKismetSystemLibrary::PrintString(this, "I've pushed someone!");
    Server_Interact();
}

void AG_Character::TogglePause()
{
    G_PlayerController = G_PlayerController.IsValid() ? G_PlayerController : Cast<AG_PlayerController>(Controller);
    if (!G_PlayerController.IsValid()) return;

    G_PlayerController->TogglePause();
}

void AG_Character::ToggleStats()
{
    G_PlayerController = G_PlayerController.IsValid() ? G_PlayerController : Cast<AG_PlayerController>(Controller);
    if (!G_PlayerController.IsValid()) return;

    G_PlayerController->ToggleStats();
}

void AG_Character::Server_Interact_Implementation()
{
    Multicast_Interact();
}

void AG_Character::Multicast_Interact_Implementation()
{
    TArray<AActor*> OverlappingActors;
    this->GetOverlappingActors(OverlappingActors);
    if (!OverlappingActors.IsEmpty())
    {
        if (IG_IInteractable* Actor = Cast<IG_IInteractable>(OverlappingActors[0]))
        {
            Actor->ReactOnPush();
        }
    }
}

UAbilitySystemComponent* AG_Character::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

UAttributeSet* AG_Character::GetAttributeSet() const
{
    return AttributeSet;
}

void AG_Character::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    InitAbilityActorInfo();
}

void AG_Character::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();

    InitAbilityActorInfo();
}

void AG_Character::OnCharacterDie()
{
    if (UWorld* World = GetWorld())
    {
        if (AG_BaseGameMode* GameMode = Cast<AG_BaseGameMode>(World->GetAuthGameMode()))
        {
            AController* RefController = GetController();
            GameMode->RespawnPawn(Controller);
        }
    }
}

void AG_Character::ReactOnPush()
{
    Jump();
    UKismetSystemLibrary::PrintString(this, "Somebody has pushed me!");
}

void AG_Character::SetKeyboardInput(bool bEnable)
{
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
                ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            if (bEnable)
            {
                Subsystem->RemoveMappingContext(WaitingForGameMappingContext);
                Subsystem->AddMappingContext(DefaultMappingContext, 0);
            }
            else
            {
                Subsystem->RemoveMappingContext(DefaultMappingContext);
                Subsystem->AddMappingContext(WaitingForGameMappingContext, 0);
            }
        }
    }
}

void AG_Character::InitAbilityActorInfo()
{
    AG_PlayerState* G_PlayerState = GetPlayerState<AG_PlayerState>();
    if (!G_PlayerState) return;

    AbilitySystemComponent = G_PlayerState->GetAbilitySystemComponent();
    AttributeSet = G_PlayerState->GetAttributeSet();

    AbilitySystemComponent->InitAbilityActorInfo(G_PlayerState, this);

    if (UG_AbilitySystemComponent* CustomAbilitySystemComponent = Cast<UG_AbilitySystemComponent>(AbilitySystemComponent))
    {
        CustomAbilitySystemComponent->AbilityActorInfoSet();
    }
}

void AG_Character::ApplyGameplayTags()
{
    if (!AbilitySystemComponent) return;

    FGameplayTagContainer AssetTags;
    AbilitySystemComponent->GetOwnedGameplayTags(AssetTags);

    for (const FGameplayTag& Tag : AssetTags)
    {
        FGameplayTag StateTag = FGameplayTag::RequestGameplayTag(FName("State"));
        if (Tag.MatchesTag(StateTag))
        {
            // Confirm States
            if (Tag.GetTagName() == "State.Debuff.Stunned")
            {
            }
        }
    }
}

void AG_Character::ApplyAttributes()
{
    UG_AttributeSet* G_AttributeSet = Cast<UG_AttributeSet>(AttributeSet);
    if (!G_AttributeSet) return;
    GetCharacterMovement()->MaxWalkSpeed = G_AttributeSet->GetMaxMovementSpeed();
}
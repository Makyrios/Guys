// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/GuysCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/G_PlayerState.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/G_AbilitySystemComponent.h"

//////////////////////////////////////////////////////////////////////////
// AGuysCharacter

AGuysCharacter::AGuysCharacter()
{
    // Set size for collision capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // Don't rotate when the controller rotates. Let that just affect the camera.
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true;             // Character moves in the direction of input...
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);  // ...at this rotation rate

    // Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
    // instead of recompiling to adjust them
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

    // Create a camera boom (pulls in towards the player if there is a collision)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;        // The camera follows at this distance behind the character
    CameraBoom->bUsePawnControlRotation = true;  // Rotate the arm based on the controller

    // Create a follow camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);  // Attach the camera to the end of the boom and let the
                                                                                 // boom adjust to match the controller orientation
    FollowCamera->bUsePawnControlRotation = false;                               // Camera does not rotate relative to arm

    // Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character)
    // are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

UAbilitySystemComponent* AGuysCharacter::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

UAttributeSet* AGuysCharacter::GetAttributeSet() const
{
    return AttributeSet;
}

void AGuysCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    // init ability actor info for the server
    InitAbilityActorInfo();
}

void AGuysCharacter::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();

    // init ability actor info for the client
    InitAbilityActorInfo();
}

void AGuysCharacter::InitAbilityActorInfo()
{
    AG_PlayerState* G_PlayerState = GetPlayerState<AG_PlayerState>();
    check(G_PlayerState);

    AbilitySystemComponent = G_PlayerState->GetAbilitySystemComponent();
    AttributeSet = G_PlayerState->GetAttributeSet();

    AbilitySystemComponent->InitAbilityActorInfo(G_PlayerState, this);
    Cast<UG_AbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}

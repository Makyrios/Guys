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
#include "Kismet/KismetSystemLibrary.h"
#include <GameModes/G_BaseGameMode.h>

#include "Kismet/GameplayStatics.h"
#include "Save/G_SaveGame.h"
#include "Player/G_PlayerController.h"
#include "Components/G_PhysicalAnimComponent.h"
#include "Components/G_InventoryComponent.h"
#include <Interfaces/G_Interactable.h>
#include <Kismet/GameplayStatics.h>

#include "Kismet/KismetInputLibrary.h"

AG_Character::AG_Character()
{
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

    GetCharacterMovement()->JumpZVelocity = 400.f;
    GetCharacterMovement()->AirControl = 0.1f;
    GetCharacterMovement()->MaxWalkSpeed = 100;
    GetCharacterMovement()->MaxAcceleration = 1024.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    PhysicalAnimComponent = CreateDefaultSubobject<UG_PhysicalAnimComponent>(TEXT("PhysicalAnimComponent"));
    InventoryComponent = CreateDefaultSubobject<UG_InventoryComponent>(TEXT("Inventory"));
    InventoryComponent->SetIsReplicated(true);
    
    Hat = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hat"));
    Hat->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("Hat_Socket_0"));
}

void AG_Character::BeginPlay()
{
    Super::BeginPlay();
    UpdateSkins();
}

void AG_Character::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AG_Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AG_Character::Move);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AG_Character::Look);
        EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AG_Character::Interact);
        EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &AG_Character::TogglePause);
        EnhancedInputComponent->BindAction(StatsAction, ETriggerEvent::Started, this, &AG_Character::ToggleStats);
        EnhancedInputComponent->BindAction(StatsAction, ETriggerEvent::Completed, this, &AG_Character::ToggleStats);
        EnhancedInputComponent->BindAction(UseAction, ETriggerEvent::Started, this, &AG_Character::Use);
        EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Started, this, &AG_Character::Select);
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

void AG_Character::Use()
{
    if (!InventoryComponent)
    {
        return;
    }

    UG_InventoryComponent* Inventory = InventoryComponent.Get();
    TSubclassOf<UGameplayAbility> AbilityToUse = Inventory->GetCurrentAbility();

    AG_PlayerState* PState = Cast<AG_PlayerState>(GetPlayerState());

    if (PState && AbilityToUse)
    {
        bool bSuccess = PState->GetAbilitySystemComponent()->TryActivateAbilityByClass(AbilityToUse, true);
        Inventory->RemoveAbility(0);
    }
}

void AG_Character::Select()
{
    if (!InventoryComponent)
    {
        return;
    }
    InventoryComponent->SelectAbility();
}

void AG_Character::Jump()
{
    if (GetWorldTimerManager().IsTimerActive(JumpTimer)) return;

    if (AttributeSet == nullptr) return;

    UG_AttributeSet* GAttributeSet = Cast<UG_AttributeSet>(AttributeSet);

    GetWorld()->GetTimerManager().SetTimer(JumpTimer, GAttributeSet->GetJumpCooldown(), false);

    Super::Jump();
}

void AG_Character::Interact(const FInputActionValue& Value)
{
    Server_Interact();
}

void AG_Character::Server_Interact_Implementation()
{
    if (bCanInteract)
    {
        TArray<AActor*> OverlappingActors;
        this->GetOverlappingActors(OverlappingActors);
        if (!OverlappingActors.IsEmpty())
        {
            for (auto& OverlappingActor : OverlappingActors)
            {
                if (OverlappingActor->Implements<UG_Interactable>())
                {
                    FVector PushDirection = (OverlappingActor->GetActorLocation() - this->GetActorLocation()).GetSafeNormal();
                    Multicast_Interact(OverlappingActor, PushDirection);
                    bCanInteract = false;

                    if (AttributeSet == nullptr) return;

                    UG_AttributeSet* GAttributeSet = Cast<UG_AttributeSet>(AttributeSet);

                    GetWorldTimerManager().SetTimer(
                        InteractTimer, [this]() { bCanInteract = true; }, GAttributeSet->GetInteractCooldown(), false);
                    break;
                }
            }
        }
    }
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

void AG_Character::Multicast_Interact_Implementation(AActor* Actor, FVector Direction)
{
    if (IG_Interactable* OtherActor = Cast<IG_Interactable>(Actor))
    {
        OtherActor->ReactOnPush(Direction);
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

void AG_Character::ReactOnPush(FVector PushDirection)
{
    if (PhysicalAnimComponent)
    {
        PhysicalAnimComponent->TogglePhysicalAnimation(2.0f);
        this->LaunchCharacter(PushDirection * 1000, false, false);
    }
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

void AG_Character::CreateSaveFile()
{
    UG_SaveGame* dataToSave = Cast<UG_SaveGame>(UGameplayStatics::CreateSaveGameObject(UG_SaveGame::StaticClass()));
    dataToSave->ChosenSkins.SkinIdx = ChosenSkinIdx;
    dataToSave->ChosenSkins.HatIdx = ChosenHatIdx;
    UGameplayStatics::SaveGameToSlot(dataToSave, "Slot1", 0);
}

void AG_Character::SaveSkinsInfo()
{
    if (!UGameplayStatics::DoesSaveGameExist("Slot1", 0))
    {
        CreateSaveFile();
    }
    UG_SaveGame* dataToSave = Cast<UG_SaveGame>(UGameplayStatics::LoadGameFromSlot("Slot1", 0));
    dataToSave->ChosenSkins.SkinIdx = ChosenSkinIdx;
    dataToSave->ChosenSkins.HatIdx = ChosenHatIdx;
    UGameplayStatics::SaveGameToSlot(dataToSave, "Slot1", 0);
}

void AG_Character::LoadSkinsInfo()
{
    if (!UGameplayStatics::DoesSaveGameExist("Slot1", 0))
    {
        CreateSaveFile();
    }
    const UG_SaveGame* savedData = Cast<UG_SaveGame>(UGameplayStatics::LoadGameFromSlot("Slot1", 0));
    ChosenSkinIdx = savedData->ChosenSkins.SkinIdx;
    ChosenHatIdx = savedData->ChosenSkins.HatIdx;

    SetSkinByIndex(ChosenSkinIdx);
    SetHatByIndex(ChosenHatIdx);
}

void AG_Character::UpdateSkins()
{
    LoadSkinsInfo();
    SetSkinByIndex(ChosenSkinIdx);
    SetHatByIndex(ChosenHatIdx);
}

void AG_Character::ChaneSkinByIndex(const int32& Mat_Idx)
{
    SetSkinByIndex(Mat_Idx);
    SaveSkinsInfo();
}

void AG_Character::ChaneHatByIndex(const int32& Hat_Idx)
{
    SetHatByIndex(Hat_Idx);
    SaveSkinsInfo();
}

void AG_Character::SetSkinByIndex_Implementation(const int32& Mat_Idx)
{
    this->GetMesh()->SetMaterial(0, Skins[Mat_Idx]);
    ChosenSkinIdx = Mat_Idx;
}

void AG_Character::SetHatByIndex_Implementation(const int32& Hat_Idx)
{
    FString SocketName = TEXT("Hat_Socket_");
    SocketName.Append(FString::FromInt(Hat_Idx));
    Hat->SetStaticMesh(Hats[Hat_Idx]);
    Hat->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName(SocketName));
    ChosenHatIdx = Hat_Idx;
}

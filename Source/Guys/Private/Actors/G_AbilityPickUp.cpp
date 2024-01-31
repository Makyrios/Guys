#include "Actors/G_AbilityPickUp.h"
#include "Character/G_Character.h"
#include "Player/G_PlayerState.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/G_InventoryComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include <Net/UnrealNetwork.h>

AG_AbilityPickUp::AG_AbilityPickUp()
{
    PrimaryActorTick.bCanEverTick = true;

    PickUpArea = CreateDefaultSubobject<USphereComponent>(TEXT("PickUp Area"));
    PickUpArea->SetupAttachment(RootComponent);

    PickUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickUp Mesh"));
    PickUpMesh->SetupAttachment(PickUpArea);

    VisualEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("VFX"));
    VisualEffect->SetupAttachment(PickUpArea);
}

void AG_AbilityPickUp::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AG_AbilityPickUp, bInRecovery);
    DOREPLIFETIME(AG_AbilityPickUp, bIsActive);
}

void AG_AbilityPickUp::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        if (PickUpArea)
        {
            PickUpArea->OnComponentBeginOverlap.AddDynamic(this, &AG_AbilityPickUp::OnBeginOverlap);
        }
    }
}

void AG_AbilityPickUp::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!bIsActive)
    {
        return;
    }

    AG_Character* OverlapCharacter = Cast<AG_Character>(OtherActor);

    if (OverlapCharacter)
    {
        bool bCanPickUp = OverlapCharacter->InventoryComponent.Get()->CanCollectAbilities();
        if (bCanPickUp)
        {
            OverlapCharacter->InventoryComponent.Get()->AddAbility(RandomChooseAbilityFromPool());
            WasCollected();
        }
    }
}

TSubclassOf<UGameplayAbility> AG_AbilityPickUp::RandomChooseAbilityFromPool()
{
    if (AbilityPool.Num() > 0)
    {
        int32 RandIndex = FMath::RandRange(0, AbilityPool.Num() - 1);
        return AbilityPool[RandIndex];
    }
    return TSubclassOf<UGameplayAbility>();
}

void AG_AbilityPickUp::WasCollected()
{
    if (!bInRecovery)
    {
        GetWorldTimerManager().SetTimer(RecoveryTimer, this, &AG_AbilityPickUp::Recovery, RecoveryTime, false, RecoveryTime);

        bInRecovery = true;

        SetActorHiddenInGame(true);
        PickUpMesh->SetVisibility(false);

        SetPickUpStatus(false);
    }
}

void AG_AbilityPickUp::Recovery()
{
    bInRecovery = false;

    SetActorHiddenInGame(false);
    PickUpMesh->SetVisibility(true);
    SetPickUpStatus(true);
}

void AG_AbilityPickUp::SetPickUpStatus(bool bStatus)
{
    bIsActive = bStatus;

    if (PickUpArea)
    {
        if (!bIsActive)
        {
            PickUpArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        }
        else
        {
            PickUpArea->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
            PickUpArea->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
        }
    }
}

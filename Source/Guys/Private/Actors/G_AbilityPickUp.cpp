#include "Actors/G_AbilityPickUp.h"
#include "Character/G_Character.h"
#include "Player/G_PlayerState.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/G_InventoryComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values
AG_AbilityPickUp::AG_AbilityPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickUpArea = CreateDefaultSubobject<USphereComponent>(TEXT("PickUp Area"));
	PickUpArea->SetupAttachment(RootComponent);

	PickUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickUp Mesh"));
	PickUpMesh->SetupAttachment(PickUpArea);

	VisualEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("VFX"));
	VisualEffect->SetupAttachment(PickUpArea);
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

// Called when the game starts or when spawned
void AG_AbilityPickUp::BeginPlay()
{
	Super::BeginPlay();

	if (PickUpArea)
	{
		PickUpArea->OnComponentBeginOverlap.AddDynamic(this, &AG_AbilityPickUp::OnBeginOverlap);
	}

}

void AG_AbilityPickUp::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

void AG_AbilityPickUp::Recovery()
{
	bInRecovery = false;

	SetActorHiddenInGame(false);

	SetPickUpStatus(true);
}

void AG_AbilityPickUp::WasCollected()
{
	if (!bInRecovery)
	{
		GetWorldTimerManager().SetTimer(RecoveryTimer, this, &AG_AbilityPickUp::Recovery, RecoveryTime, false, RecoveryTime);

		bInRecovery = true;

		SetActorHiddenInGame(true);

		SetPickUpStatus(false);
	}
}

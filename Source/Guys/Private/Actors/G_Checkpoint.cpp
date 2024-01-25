// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/G_Checkpoint.h"
#include "Components/BoxComponent.h"
#include <Player/G_PlayerState.h>
#include <Kismet/KismetMathLibrary.h>

AG_Checkpoint::AG_Checkpoint()
{
	PrimaryActorTick.bCanEverTick = false;

    SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
    RootComponent = SceneComponent;

    CheckpointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Checkpoint Mesh"));
    CheckpointMesh->SetupAttachment(SceneComponent);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
    BoxCollider->SetupAttachment(CheckpointMesh);
    BoxCollider->SetCollisionProfileName(FName("OverlapOnlyPawn"));
    BoxCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
}

FVector AG_Checkpoint::GetRandomSpawnPoint() const
{
    check(BoxCollider);
    return UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), FVector(0, BoxCollider->GetScaledBoxExtent().X, 0));
}

void AG_Checkpoint::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AG_Checkpoint::HandleCheckpointOverlap);
    BoxCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AG_Checkpoint::HandleCheckpointOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (APawn* Pawn = Cast<APawn>(OtherActor))
    {
        if (AG_PlayerState* PlayerState = Pawn->GetPlayerState<AG_PlayerState>())
        {
            if (!bTriggeredBefore)
            {
                PlayerState->AddPlayerScore(Points);
                bTriggeredBefore = true;
            }
            PlayerState->SetLastCheckpoint(this);
        }
    }
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/G_Checkpoint.h"
#include "Components/BoxComponent.h"

AG_Checkpoint::AG_Checkpoint()
{
	PrimaryActorTick.bCanEverTick = false;

    CheckpointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Checkpoint Mesh"));
    RootComponent = CheckpointMesh;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
    BoxCollider->SetupAttachment(CheckpointMesh);
}

void AG_Checkpoint::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AG_Checkpoint::HandleCheckpointOverlap);
    BoxCollider->SetCollisionProfileName(FName("OverlapOnlyPawn"));
}

void AG_Checkpoint::HandleCheckpointOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Display, TEXT("Overlap Checkpoint"));
    /* TODO
    if (APawn* Pawn = Cast<APawn>(OtherActor))
    {
        if (AG_CustomPlayerState* PlayerState = Pawn->GetPlayerState<AG_CustomPlayerState>())
        {
            if (!bTriggeredBefore)
            {
                PlayerState->AddPoints(Points);
                bTriggeredBefore = true;
            }
            PlayerState->SetSpawnLocation(GetActorLocation());
        }
    }*/
}

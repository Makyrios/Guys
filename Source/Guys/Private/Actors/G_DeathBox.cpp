// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/G_DeathBox.h"
#include <Components/BoxComponent.h>
#include <Character/G_Character.h>


AG_DeathBox::AG_DeathBox()
{
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
    Box->SetCollisionProfileName(FName("OverlapOnlyPawn"));
}

void AG_DeathBox::BeginPlay()
{
	Super::BeginPlay();
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &AG_DeathBox::OnBoxBeginOverlap);
}

void AG_DeathBox::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (AG_Character* PlayerCharacter = Cast<AG_Character>(OtherActor))
    {
        PlayerCharacter->OnCharacterDie();
    }
}

void AG_DeathBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


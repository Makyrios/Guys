// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/G_PhysicalAnimComponent.h"

UG_PhysicalAnimComponent::UG_PhysicalAnimComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UG_PhysicalAnimComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* Owner = GetOwner())
	{
		PhysicalAnimComponent = Cast<UPhysicalAnimationComponent>(
			Owner->AddComponentByClass(UPhysicalAnimationComponent::StaticClass(), true, FTransform(), false));
		
		SkeletalMeshComponent = Cast<USkeletalMeshComponent>(
			Owner->GetComponentByClass(USkeletalMeshComponent::StaticClass()));

		PhysicalAnimComponent->SetSkeletalMeshComponent(SkeletalMeshComponent);
	}
}


void UG_PhysicalAnimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UG_PhysicalAnimComponent::TogglePhysicalAnimation()
{
	SkeletalMeshComponent->SetAllBodiesBelowSimulatePhysics("Spine1", true, false);
}


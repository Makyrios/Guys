// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/G_PhysicalAnimComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UG_PhysicalAnimComponent::UG_PhysicalAnimComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UG_PhysicalAnimComponent::BeginPlay()
{
	Super::BeginPlay();

	SimulationBone = FName("Spine1");

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
	if (SkeletalMeshComponent && PhysicalAnimComponent)
	{
		FPhysicalAnimationData Data;
		Data.bIsLocalSimulation = true;
		Data.OrientationStrength = 1000.f;
		Data.AngularVelocityStrength = 100.f;
		Data.PositionStrength = 1000.f;
		Data.VelocityStrength = 100.f;
		Data.MaxLinearForce = 100.f;
		Data.MaxAngularForce = 100.f;

		PhysicalAnimComponent->ApplyPhysicalAnimationSettingsBelow(SimulationBone, Data);
		SkeletalMeshComponent->SetAllBodiesBelowSimulatePhysics(SimulationBone, true, false);
		UKismetSystemLibrary::PrintString(this, "Physics simulated!");
	}
}


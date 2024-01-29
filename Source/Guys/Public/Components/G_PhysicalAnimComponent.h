// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "G_PhysicalAnimComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GUYS_API UG_PhysicalAnimComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UG_PhysicalAnimComponent();

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void TogglePhysicalAnimation();
		
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UPhysicalAnimationComponent> PhysicalAnimComponent;

	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
};

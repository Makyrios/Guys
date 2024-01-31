// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "G_AbilityPickUp.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UNiagaraComponent;
class UGameplayAbility;

UCLASS()
class GUYS_API AG_AbilityPickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AG_AbilityPickUp();

public:
	void SetPickUpStatus(bool bStatus);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FTimerHandle RecoveryTimer;

private:
	TSubclassOf<UGameplayAbility> RandomChooseAbilityFromPool();

	void Recovery();

	void WasCollected();

private:
	UPROPERTY(EditAnywhere, Category = "G|Components")
	USphereComponent* PickUpArea;

	UPROPERTY(EditAnywhere, Category = "G|Components")
	UStaticMeshComponent* PickUpMesh;

	UPROPERTY(EditAnywhere, Category = "G|Components")
	UNiagaraComponent* VisualEffect;

	UPROPERTY(EditAnywhere, Category = "G|Properties")
	uint32 RecoveryTime = 10.0f;

	UPROPERTY(EditAnywhere, Category = "G|Properties")
	TArray<TSubclassOf<UGameplayAbility>> AbilityPool;

	bool bInRecovery = false;

	bool bIsActive = true;
};

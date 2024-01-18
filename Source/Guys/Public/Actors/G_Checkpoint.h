// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "G_Checkpoint.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class GUYS_API AG_Checkpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	AG_Checkpoint();

    FVector GetRandomSpawnPoint() const;

protected:
	virtual void BeginPlay() override;

    UFUNCTION()
	virtual void HandleCheckpointOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
    UPROPERTY(VisibleAnywhere, Category = "G|Components")
    TObjectPtr<USceneComponent> SceneComponent;
    UPROPERTY(VisibleAnywhere, Category = "G|Components")
    TObjectPtr<UStaticMeshComponent> CheckpointMesh;
    UPROPERTY(VisibleAnywhere, Category = "G|Components")
    TObjectPtr<UBoxComponent> BoxCollider;

    UPROPERTY(EditAnywhere, Category = "G|Checkpoint")
    int Points = 10;


private:
    bool bTriggeredBefore = false;

};

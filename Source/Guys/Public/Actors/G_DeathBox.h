// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "G_DeathBox.generated.h"

class UBoxComponent;

UCLASS()
class GUYS_API AG_DeathBox : public AActor
{
	GENERATED_BODY()
	
public:	
	AG_DeathBox();

	UPROPERTY(VisibleAnywhere, Category = "G|Components")
    TObjectPtr<UBoxComponent> Box;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

public:	
	virtual void Tick(float DeltaTime) override;

};

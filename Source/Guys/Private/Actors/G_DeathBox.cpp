// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/G_DeathBox.h"

// Sets default values
AG_DeathBox::AG_DeathBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AG_DeathBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AG_DeathBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


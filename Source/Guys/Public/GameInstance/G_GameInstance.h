// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "G_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GUYS_API UG_GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;

	UFUNCTION()
	void BeginLoadingScreen(const FString& InMapName);

public:
	UPROPERTY(EditDefaultsOnly, Category = "AS|LoadingScreen")
	TSubclassOf<UUserWidget> LoadingScreenClass;
};

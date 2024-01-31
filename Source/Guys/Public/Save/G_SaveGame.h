// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Structs\G_ChosenSkinsIdx.h"
#include "G_SaveGame.generated.h"
/**
 * 
 */
UCLASS()
class GUYS_API UG_SaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	UPROPERTY()
	FG_ChosenSkinsIdx ChosenSkins;
	
	UG_SaveGame()
	{
		ChosenSkins.SkinIdx = 0;
		ChosenSkins.HatIdx = 0;
	}
};

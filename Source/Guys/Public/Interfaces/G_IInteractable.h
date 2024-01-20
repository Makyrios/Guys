// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "G_IInteractable.generated.h"

UINTERFACE(MinimalAPI)
class UG_IInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GUYS_API IG_IInteractable
{
	GENERATED_BODY()

public:
	virtual void ReactOnPush();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "G_Interactable.generated.h"

UINTERFACE(MinimalAPI)
class UG_Interactable : public UInterface
{
	GENERATED_BODY()
};

class GUYS_API IG_Interactable
{
	GENERATED_BODY()

public:
	virtual void ReactOnPush(FVector PushDirection) PURE_VIRTUAL(&IG_Interactable::ReactOnPush,);
};

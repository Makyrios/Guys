// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameRules/GuysGameMode.h"
#include "Character/GuysCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGuysGameMode::AGuysGameMode()
{
    // set default pawn class to our Blueprinted character
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
    if (PlayerPawnBPClass.Class != nullptr)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
}

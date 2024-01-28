#pragma once

#include "CoreMinimal.h"
#include "G_BaseGameMode.h"
#include "G_LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GUYS_API AG_LobbyGameMode : public AG_BaseGameMode
{
	GENERATED_BODY()

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;

public:
	UPROPERTY(EditAnywhere, Category = "G|Maps")
	TMap<FString, FString> MapsForModes;
};

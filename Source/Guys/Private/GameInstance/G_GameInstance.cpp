// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/G_GameInstance.h"
#include "Blueprint/UserWidget.h"
#include "MoviePlayer/Public/MoviePlayer.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Slate.h"

void UG_GameInstance::Init()
{
    Super::Init();
    FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UG_GameInstance::BeginLoadingScreen);
}

void UG_GameInstance::BeginLoadingScreen(const FString& InMapName)
{
    UE_LOG(LogTemp, Warning, TEXT("BeginLoadingScreen is launched"));
    if (IsRunningDedicatedServer()) return;

    FLoadingScreenAttributes Attributes;
    Attributes.bAutoCompleteWhenLoadingCompletes = false;
    Attributes.bMoviesAreSkippable = true;
    Attributes.MinimumLoadingScreenDisplayTime = 2.f;

    UUserWidget* LoadingScreen = CreateWidget<UUserWidget>(GetWorld(), LoadingScreenClass);
    if (!LoadingScreen) return;

    Attributes.WidgetLoadingScreen = LoadingScreen->TakeWidget();

    IGameMoviePlayer* MoviePlayer = GetMoviePlayer();
    if (MoviePlayer)
    {
        MoviePlayer->SetupLoadingScreen(Attributes);
    }
}
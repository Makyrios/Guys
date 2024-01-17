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
    FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UG_GameInstance::EndLoadingScreen);
}

void UG_GameInstance::BeginLoadingScreen(const FString& MapName)
{
    UE_LOG(LogTemp, Warning, TEXT("BeginLoadingScreen is launched"));
    if (IsRunningDedicatedServer()) return;

    FLoadingScreenAttributes Attributes;
    Attributes.bAutoCompleteWhenLoadingCompletes = false;
    Attributes.MinimumLoadingScreenDisplayTime = 2.f;

    UUserWidget* LoadingScreen = CreateWidget<UUserWidget>(GetWorld(), LoadingScreenClass);
    if (!LoadingScreen) return;

    Attributes.WidgetLoadingScreen = LoadingScreen->TakeWidget();

    if (GetMoviePlayer())
    {
        GetMoviePlayer()->SetupLoadingScreen(Attributes);
    }
}

void UG_GameInstance::EndLoadingScreen(UWorld* InLoadedWorld)
{

}

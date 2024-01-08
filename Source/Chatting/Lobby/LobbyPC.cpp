// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPC.h"
#include "LobbyWidgetBase.h"



void ALobbyPC::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = true;

	//FSoftObjectPath 블프 가져오는거 하드코딩
	FSoftClassPath LobbyWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Lobby/WBP_Lobby.WBP_Lobby_C'"));//인클루드 경로만

	UClass* WidgetClass = LobbyWidgetClass.TryLoadClass<ULobbyWidgetBase>();// 인클루드.
	if (WidgetClass && IsLocalPlayerController())
	{
		LobbyWidgetObject= CreateWidget<ULobbyWidgetBase>(this, WidgetClass);//new 부분
		if (LobbyWidgetObject)
		{
			LobbyWidgetObject->AddToViewport();//껏다켰다가 성능에 좋다
		}
	}
}

bool ALobbyPC::C2S_SendMessage_Validate(const FString& InMessage)
{
	return true;
}

void ALobbyPC::C2S_SendMessage_Implementation(const FString& InMessage)
{
	for (auto It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		ALobbyPC* PC = Cast<ALobbyPC>(*It);
		if(PC)
		{
			PC->S2C_SendMessage(InMessage);
		}
	}
}

void ALobbyPC::S2C_SendMessage_Implementation(const FString& InMessage)
{
	if (LobbyWidgetObject)
	{
		LobbyWidgetObject->AddMessage(InMessage);
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPC.h"
#include "LobbyWidgetBase.h"



void ALobbyPC::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = true;

	//FSoftObjectPath ���� �������°� �ϵ��ڵ�
	FSoftClassPath LobbyWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Lobby/WBP_Lobby.WBP_Lobby_C'"));//��Ŭ��� ��θ�

	UClass* WidgetClass = LobbyWidgetClass.TryLoadClass<ULobbyWidgetBase>();// ��Ŭ���.
	if (WidgetClass && IsLocalPlayerController())
	{
		LobbyWidgetObject= CreateWidget<ULobbyWidgetBase>(this, WidgetClass);//new �κ�
		if (LobbyWidgetObject)
		{
			LobbyWidgetObject->AddToViewport();//�����״ٰ� ���ɿ� ����
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

// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidgetBase.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "LobbyPC.h"



void ULobbyWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerCountTextBox = Cast<UTextBlock>(GetWidgetFromName("PlayerCountTextBox"));
	ChatScrollBox = Cast<UScrollBox>(GetWidgetFromName("ChatScrollBox"));
	ChatInputTextBox = Cast<UEditableTextBox>(GetWidgetFromName("ChatInputTextBox"));
	if (ChatInputTextBox)
	{
		ChatInputTextBox->OnTextChanged.AddDynamic(this, &ULobbyWidgetBase::ProccessChanged);
		ChatInputTextBox->OnTextCommitted.AddDynamic(this, &ULobbyWidgetBase::ProccessCommitted);
	}

	LeftTimeTextBox = Cast<UTextBlock>(GetWidgetFromName("LeftTimeTextBox"));
}
void ULobbyWidgetBase::ProccessChanged(const FText& Text)
{

}
void ULobbyWidgetBase::ProccessCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	ALobbyPC* PC = Cast<ALobbyPC>(GetOwningPlayer());

	if (PC)
	{
		switch (CommitMethod)
		{
		case  ETextCommit::OnEnter:
			PC->C2S_SendMessage(ChatInputTextBox->GetText().ToString());
			ChatInputTextBox->SetText(FText::FromString(TEXT("")));
			break;

		case  ETextCommit::OnCleared:
			ChatInputTextBox->SetUserFocus(PC);
			break;
		}
	}
	
}

void ULobbyWidgetBase::UpdatePlayerCount(int32 InplayerCount)
{
	if (PlayerCountTextBox)
	{
		FString Message = FString::Printf(TEXT("%d "), InplayerCount);
		PlayerCountTextBox->SetText(FText::FromString(Message));
	}
	

}

void ULobbyWidgetBase::AddMessage(const FString& InMessge)
{
	if (ChatScrollBox)
	{
		UTextBlock* NewMessage = NewObject<UTextBlock>(ChatScrollBox);//newobject는 아웃터를 만들어줘야함.
		if (NewMessage)
		{
			NewMessage->SetText(FText::FromString(InMessge));
			FSlateFontInfo NewFont = NewMessage->GetFont();
			NewFont.Size = 18;
			NewMessage->SetFont(NewFont);
			ChatScrollBox->AddChild(NewMessage);
			ChatScrollBox->ScrollToEnd();
		}
	}
}

void ULobbyWidgetBase::UpdateLeftTime(int InLeftTime)
{
	if (LeftTimeTextBox)
	{
		if (InLeftTime > 0)
		{
			FString Message = FString::Printf(TEXT("%d초 남음"), InLeftTime);
			LeftTimeTextBox->SetText(FText::FromString(Message));
		}
		else
		{
			FString Message = FString::Printf(TEXT("시작"));
		}
	}
}

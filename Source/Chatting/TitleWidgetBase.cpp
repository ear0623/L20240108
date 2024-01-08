// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleWidgetBase.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"

void UTitleWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	MakeRoomButton= Cast<UButton>(GetWidgetFromName(TEXT("MakeRoomButton")));
	CunnectServerButton = Cast<UButton>(GetWidgetFromName(TEXT("CunnectServerButton")));
	IPTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("IPTextBox")));

	if (MakeRoomButton)
	{
		MakeRoomButton->OnClicked.AddDynamic(this, &UTitleWidgetBase::ProcessMakeRoom);//���ٸ���
	}
	if (CunnectServerButton)
	{
		CunnectServerButton->OnClicked.AddDynamic(this, &UTitleWidgetBase::ProcessConnectServer);
	}
}

void UTitleWidgetBase::ProcessMakeRoom()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Lobby"), true, TEXT("listen"));
}

void UTitleWidgetBase::ProcessConnectServer()
{
	if (IPTextBox)
	{
		//�ϱ��� ����ó��.�־�ߵ�
		UGameplayStatics::OpenLevel(GetWorld(), FName(*IPTextBox->GetText().ToString()));
		//FName-> HashTable �˻� �������� ���ڷ� ��ȯ��. ��ҹ��� ���и���.
		//FText-> �ٱ��� ���̺�/���̺��̶� ����ȵ�
		//FText-> �񱳴� ���� ����
		//Tag->FName;
		//findssession ��������ΰ� �˰� ����
	}
}
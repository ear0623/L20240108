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
		MakeRoomButton->OnClicked.AddDynamic(this, &UTitleWidgetBase::ProcessMakeRoom);//람다못씀
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
		//하기전 에러처리.넣어야되
		UGameplayStatics::OpenLevel(GetWorld(), FName(*IPTextBox->GetText().ToString()));
		//FName-> HashTable 검색 한자한자 숫자로 변환함. 대소문자 구분못함.
		//FText-> 다국어 테이블/테이블이라 변경안됨
		//FText-> 비교는 좋지 않음
		//Tag->FName;
		//findssession 옛날방식인거 알고 공부
	}
}
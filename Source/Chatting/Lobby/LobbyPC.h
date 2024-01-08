// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPC.generated.h"

class ULobbyWidgetBase;
/**
 * 
 */
UCLASS()
class CHATTING_API ALobbyPC : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category= "UI")
	TObjectPtr<ULobbyWidgetBase> LobbyWidgetObject;//그냥 포인터를 관리하기 위해 ue5에서 만든 포인터문법

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")//blueprint에 노출하겠다면//
	//TSubclassOf<ULobbyWidgetBase> LobbyWidgetClass;//설정 후 add to viewport 
	//클래스 자체를 기억하고, 사용.
	UFUNCTION(Server,Unreliable,WithValidation)//reliable -- packing 100%가 일치해야함//전재 절대 안믿음
	void C2S_SendMessage(const FString& InMessage);//client call

	bool C2S_SendMessage_Validate(const FString& InMessage);

	void C2S_SendMessage_Implementation(const FString& InMessage);//serverexcute

	UFUNCTION(Client,Reliable)//클라이언트에서 실행 서버에서 동작//서버는 무적권 믿음
	void S2C_SendMessage(const FString& InMessage);//server call

	void S2C_SendMessage_Implementation(const FString& InMessage);//serverexcute
};
